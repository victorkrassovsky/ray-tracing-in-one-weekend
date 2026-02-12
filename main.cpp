#include <iostream>

#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#define SPHERE_RADIUS 0.5
#define SPHERE_CENTER point3(0,0,-1)

#define GROUND_RADIUS 100
#define GROUND_CENTER point3(0,-100.5,-1)


int main(){
  // World

  hittable_list world;

  world.add(make_shared<sphere>(SPHERE_CENTER, SPHERE_RADIUS));
  world.add(make_shared<sphere>(GROUND_CENTER, GROUND_RADIUS));

  camera cam;
  cam.aspect_ratio = 16.0/9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;

  cam.render(world);
}
