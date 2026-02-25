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

  auto ground_material = make_shared<lambertian>(color(0.8, 0.8, 0.8));
  world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, ground_material));

  shared_ptr<material> left = make_shared<lambertian>(color(0.3, 0.8, 0.3));
  shared_ptr<material> middle = make_shared<lambertian>(color(0.7, 0.7, 0.7));
  shared_ptr<material> right = make_shared<lambertian>(color(0.1, 0.1, 0.4));

  shared_ptr<material> glass = make_shared<dielectric>(1.2);

  shared_ptr<material> clear_metal = make_shared<metal>(color(0.6,0.6,0.6), 0.1);

  //world.add(make_shared<sphere>(point3(0,1,4), 1, metal_left));
  world.add(make_shared<triangle>(point3(-1,-0.75,5),point3(0,0.25,3),point3(1,-0.75,5), clear_metal));
  world.add(make_shared<triangle>(point3(-1,-0.75,5),point3(0,0.25,3),point3(-0.75,0.25,2), left));
  world.add(make_shared<triangle>(point3(0.75,0.25,2),point3(0,0.25,3),point3(1,-0.75,5), right));

  world.add(make_shared<sphere>(point3(-0.5, -0.25, 2.3), 0.25, glass));

  world.add(make_shared<triangle>(point3(0.5, -0.25, 1.5),
				  point3(0, 0.125, 2.75),
				  point3(0, -0.5, 2.5),
				  clear_metal));
  
  world.add(make_shared<sphere>(point3(0, -0.3, 3), 0.1, middle));
  
  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 1600;
  cam.samples_per_pixel = 200;
  cam.max_depth         = 40;

  cam.vfov     = 25;
  cam.camera_pos = point3(0,0,0);
  cam.lookat   = point3(0,0,5);
  cam.up      = vec3(0,1,0);

  cam.render(world);
}
