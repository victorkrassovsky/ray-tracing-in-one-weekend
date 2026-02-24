#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"

class triangle : public hittable {
 private:
  point3 p1,p2,p3;
  vec3 n;
  double d;
  shared_ptr<material> mat;

 public:
 triangle(const point3& p1, const point3& p2, const point3& p3, shared_ptr<material> mat) : p1(p1), p2(p2), p3(p3),  mat(mat) {
    n = unit_vector(cross(p2-p1, p3-p1));
    d = dot(n,p1);
  }

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override {    
    vec3 R = r.direction();
    point3 Q = r.origin();
    if (std::fabs(dot(n, R)) < 0.01){
      return false;
    }

    double t = (d - dot(n, Q)) / dot(n, R);
    
    
    if (!ray_t.contains_strict(t))
      return false;

    point3 inter = r.at(t);

    if (dot(n, cross(p2 - p1, inter - p1)) < 0.0 ||
	dot(n, cross(p3 - p2, inter - p2)) < 0.0 ||
	dot(n, cross(p1 - p3, inter - p3)) < 0.0){
      return false;
    }

    rec.t = t;
    rec.p = inter;
    rec.set_face_normal(r, n);
    rec.mat = mat;

    return true;
  }
};

#endif
