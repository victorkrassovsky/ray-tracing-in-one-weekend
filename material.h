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

#endif
