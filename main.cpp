#include <iostream>

#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main(){
  // World

  hittable_list world;

  double r = std::cos(pi/4);

  auto material_left  = make_shared<lambertian>(color(0,0,1));
  auto material_right = make_shared<lambertian>(color(1,0,0));

  world.add(make_shared<sphere>(point3(-r, 0, -1), r, material_left));
  world.add(make_shared<sphere>(point3( r, 0, -1), r, material_right));
  
  camera cam;
  cam.aspect_ratio = 16.0/9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;
  cam.vfov = 90;

  cam.render(world);
}
