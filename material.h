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
  
public:
  dialectric(double index) : index(index) {}

  bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override{
    attenuation = color(1.0,1.0,1.0);
    
    // if the ray is going out of the surface, the ratio of indices is reversed
    // the index of air is about 1.0
    double index_ratio = rec.front_face ? (1.0/index) : index;

    vec3 unit_direction = unit_vector(r.direction());
    vec3 refracted = refract(unit_direction, rec.normal, index_ratio);
    scattered = ray(rec.p, refracted);
    return true;
  }
};

#endif

