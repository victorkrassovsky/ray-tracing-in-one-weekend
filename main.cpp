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

  auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, ground_material));
  
  shared_ptr<material> metal_left = make_shared<metal>(color(0.7, 0.2, 0.2), 0.1);
  shared_ptr<material> metal_right = make_shared<metal>(color(0.2, 0.2, 0.7), 0.2);
  shared_ptr<material> middle = make_shared<lambertian>(color(0.7, 0.1, 0.7));

  //world.add(make_shared<sphere>(point3(0,1,4), 1, metal_left));
  world.add(make_shared<triangle>(point3(-1,0,5),point3(0,1,3),point3(1,0,5), middle));
  
  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 30;
  cam.max_depth         = 50;

  cam.vfov     = 90;
  cam.camera_pos = point3(0,0,0);
  cam.lookat   = point3(0,0,5);
  cam.up      = vec3(0,1,0);

  cam.render(world);
}
