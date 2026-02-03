#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
 private:
  point3 center;
  double radius;

 public:
 sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

  // returns true and updates rec if the ray and sphere intersect
  // sets rec.p to closest point
  bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
    vec3 v = center - r.origin();
    vec3 d = r.direction();
    double a = dot(d, d);
    double h = dot(d, v);
    double c = dot(v,v) - radius*radius;

    double disc = h*h - a*c;
    if (disc < 0.0){
      return false;
    }
    double sqrtd = std::sqrt(disc);
    double root1 = (h-sqrtd) / a;
    double root2 = (h+sqrtd) / a;

    double root = root1;

    if (root <= ray_tmin || root >= ray_tmax){
      root = root2;
      if (root <= ray_tmin || root >= ray_tmax){
	return false;
      }
    }

    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
  }
};


#endif
