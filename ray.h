#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
 private:
  point3 origin;
  vec3 dir;
 
 public:
  ray() {}
  const point3& origin() const {
    return origin;
  }
  const vec3& direction() const {
    return dir;
  }

  point3 at(double t) const{
    return orig + t*dir;
  }
}

#endif
