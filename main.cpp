#include <iostream>

#include "color.h"
#include "vec3.h"
#include "ray.h"

#define SPHERE_RADIUS 0.5
#define SPHERE_CENTER point3(0,0,-1)

bool hit_sphere(const ray& r, const point3 sphere_center, double radius){
  vec3 v = r.origin() - sphere_center;
  vec3 d = r.direction();
  double a = dot(d, d);
  double b = (-2)*dot(d, v);
  double c = dot(v,v) - radius*radius;

  double disc = b*b - 4*a*c;
  return disc >= 0;
}

color ray_color(const ray& r) {
  if (hit_sphere(r, SPHERE_CENTER, SPHERE_RADIUS)) {
    return color(1,0,0);
  }
  return color(1,1,1);
}


int main(){

  // Image
  double aspect_ratio = 16.0 / 9.0; // should be (image_height/image_width)
  int image_width = 400;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height; // height needs to be a positive integer

  // Camera

  double focal_length = 1.0; // distance from camera to viewport
  double viewport_height = 2.0;
  double viewport_width = viewport_height * (double(image_width)/image_height);
  point3 camera_center = point3(0,0,0);

  // vectors that go across and down the viewport
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  // distances between pixels
  vec3 pixel_delta_u = viewport_u / image_width;
  vec3 pixel_delta_v = viewport_v / image_height;

  // upper left pixel location
  point3 viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2; // upper left corner of the viewport
  point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // upper left pixel inside the viewport 

  // Render
  
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  
  for (int j = 0; j < image_height; j++){
    std::clog << "\rScanlogs remaining: " << (image_height - j) << " " << std::flush;
    for(int i = 0; i < image_width ; i++){
      point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      vec3 ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone \n";
}
