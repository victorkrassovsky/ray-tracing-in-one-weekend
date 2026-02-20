#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

// sends linear space colors to gamma space colors
inline double linear_to_gamma(double linear_component){
  if (linear_component < 0)
    return 0;
  return std::sqrt(linear_component);
}

void write_color(std::ostream& out, const color& pixel_color){
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // the image viewer expects pixel colors to be in the gamma space
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);
  
  static const interval intensity(0, 0.999);
  int rbyte = int(255.999 * intensity.clamp(r));
  int gbyte = int(255.999 * intensity.clamp(g));
  int bbyte = int(255.999 * intensity.clamp(b));

  out << rbyte << ' ' << gbyte << ' ' << bbyte << "\n";
}

#endif
