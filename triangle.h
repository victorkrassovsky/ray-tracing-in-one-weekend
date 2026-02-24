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
 triangle(const point3& p1, const point3& p2, const point3& p3, shared_ptr<material> mat) : p1(p1), p2(p2), p3(p3), n(unit_vector(cross(p1 - p2, p1 - p3))), d(dot(n,p1)), mat(mat) {}

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
    vec3 R = r.direction();
    point3 Q = r.origin();
    if (dot(n, Q) == 0.0){
      return false;
    }

    double t = (d - dot(n, Q)) / dot(n,R);
    if (!ray_t.contains_strict(t))
      return false;

    point3 inter = r.at(t);

    if (dot(n, cross(p1 - p2, p1 - inter)) < 0.0 ||
	dot(n, cross(p2 - p3, p2 - inter)) < 0.0 ||
	dot(n, cross(p3 - p1, p3 - inter)) < 0.0)
      return false;

    rec.t = t;
    rec.p = inter;
    rec.set_face_normal(r, n);
    rec.mat = mat;

    return true;
  }
};

#endif
