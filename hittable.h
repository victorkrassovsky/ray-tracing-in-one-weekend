#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"


// record for a hit with a ray and hittable
// stores the position, normal vector, and scalar for a ray 
class hit_record {
 public:
  point3 p;
  vec3 normal;
  double t;
};

// base class for hittable objects, i.e. ones that rays can hit
class hittable {
 public:
  virtual ~hittable() = default;
  
  virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const{
    return 0;
  }
    
};
  

#endif
