#include <iostream>

#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main(){
  hittable_list world;
  
  auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

  auto glass = make_shared<dialectric>(1.5);
  auto material_blue = make_shared<lambertian>(color(0.2, 0.8, 0.1));
  auto material_green = make_shared<lambertian>(color(0.2, 0.2, 0.7));
  auto material_metal = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  
  world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material_blue));
  world.add(make_shared<sphere>(point3(3, 1, 1), 0.75, material_metal));
  world.add(make_shared<sphere>(point3(2, 1, 2), 0.50, material_green));
  world.add(make_shared<sphere>(point3(1, 1, 3), 0.25, material_metal));
  world.add(make_shared<sphere>(point3(5, 0.5, 1), 0.50, glass));

  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 1600;
  cam.samples_per_pixel = 200;
  cam.max_depth         = 50;

  cam.vfov     = 20;
  cam.camera_pos = point3(13,2,3);
  cam.lookat   = point3(0,0,0);
  cam.up      = vec3(0,1,0);

  cam.render(world);
}
