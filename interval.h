#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
 public:
  double min, max;

 interval() : min(infinity), max(-infinity) {}
  
 interval(double min, double max) : min(min), max(max) {}

  double size() const {
    return max - min;
  }

  bool contains(double t) const {
    return min <= t && t <= max;
  }

  bool contains_strict(double t) const {
    return min < t && t < max;
  }

  double clamp(double t) const {
    if (t < min)
      return min;
    if (t > max)
      return max;
    return t;
  }

  static const interval empty, universe;
};

const interval interval::empty = interval(1, -1);
const interval interval::universe = interval(-infinity, infinity);

#endif
