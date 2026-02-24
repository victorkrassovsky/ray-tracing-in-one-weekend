#include <iostream>

#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "triangle.h"

int main(){
  hittable_list world;

  //shared_ptr<material> background = make_shared<lambertian>(color(0.4,0.4,0.4));
  shared_ptr<material> metal_left = make_shared<metal>(color(0.7, 0.2, 0.2), 0.1);
  shared_ptr<material> metal_right = make_shared<metal>(color(0.2, 0.2, 0.7), 0.2);
  shared_ptr<material> middle = make_shared<lambertian>(color(0.7, 0.1, 0.7));

  //world.add(make_shared<sphere>(point3(0,0,500), 450, background));
  world.add(make_shared<triangle>(point3(0,0,4),point3(0,1,4),point3(1,0,4), middle));
  
  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth         = 50;

  cam.vfov     = 90;
  cam.camera_pos = point3(0,0,0);
  cam.lookat   = point3(0,0,5);
  cam.up      = vec3(0,1,0);

  cam.render(world);
}
