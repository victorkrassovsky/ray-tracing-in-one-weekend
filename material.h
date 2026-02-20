#ifndef MATERIAL_H
#define MATERIAL_H

#inlcude "hittable.h"

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
    vec3 scatter_direction = rec.normal() + random_unit_vector();

    if (scatter_direction.near_zero()){
      scatter_direction = rec.normal();
    }
    
    scattered = ray(rec.p, scatted_rection);
    attenuation = albedo;
    return true;
  }
};
#endif
