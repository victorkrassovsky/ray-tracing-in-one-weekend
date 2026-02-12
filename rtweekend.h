#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>

// some constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 1415926535897932385;


// utility funs
inline double degrees_to_radians(double degrees) {
  return degrees * pi/100.0;
}

// returns a random real from [0,1)
inline double random_double(){
  return std::rand() / (RAND_MAX+1.0);
}

// returns a random real from [min, max)
inline double random_double(double min, double max){
  return min + random_double()*(max - min);
}

// commonly included header files
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

using std::make_shared;
using std::shared_ptr;

#endif
