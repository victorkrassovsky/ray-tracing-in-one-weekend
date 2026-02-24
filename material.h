#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material{
 public:
  virtual ~material() = default;

  virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const{
    return false;
  }
};


// standard material that diffuses according to albedo parameter
// diffuses by lambertian reflectance
class lambertian : public material {
private:
  color albedo;

public:
  lambertian(const color& albedo) : albedo(albedo) {}

  bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
    vec3 scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero()){
      scatter_direction = rec.normal;
    }
    
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }
};

// material that reflects light across its surface
// color is given by albedo
// fuzz gives perperurbation of rays that hit
class metal : public material {
private:
  color albedo;
  double fuzz;

public:
  metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz){}

  bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override{
    vec3 reflected = reflect(r.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }
};

// transparent material, refracts light according to index paramter
// reflects around the edges
class dialectric : public material{
private:
  double index;

  // Schlick's approximation
  static double reflectance(double cosine, double index) {
    double r0 = (1 - index) / (1 + index);
    r0 *= r0;
    return r0 + (1-r0)*std::pow((1 - cosine), 5);
  }
  
public:
  dielectric(double index) : index(index) {}

  bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override{
    attenuation = color(1.0,1.0,1.0);
    
    // if the ray is going out of the surface, the ratio of indices is reversed
    // the index of air is about 1.0
    double index_ratio = rec.front_face ? (1.0/index) : index;

    vec3 unit_direction = unit_vector(r.direction());
    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1 - cos_theta * cos_theta);

    // if sin_theta' = index_ratio sin_theta, so if the rhs is greater than 1,
    // theta' can't exist so there cannot be a refraction
    bool cannot_refract = index_ratio * sin_theta > 1.0; 
    vec3 direction;

    if (cannot_refract || reflectance(cos_theta, index) > random_double())
      direction = reflect(unit_direction, rec.normal); // must reflect
    else
      direction = refract(unit_direction, rec.normal, index_ratio); // can refract
    
    scattered = ray(rec.p, direction);
    return true;
  }
};

#endif

