#include "circle.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <cmath>

// for const radius, a initializer list is a MUST
// center uses the default constructor of Point to initialize
Circle::Circle() : center(Point()), radius(0) {
}

Circle::Circle(Point p, const double r) : center(p), radius(r) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  return circleIntersectionArea(
      radius, otherCircle.radius, center.distanceFrom(otherCircle.center));
}

double Circle::circleIntersectionArea(double r1, double r2, double d) {
  if (d >= r1 + r2) {
    return 0.0;  // no intersection
  }
  if (d <= fabs(r1 - r2)) {
    // one circle is entirely in the other, so return the area of the smaller one
    double r = std::fmin(r1, r2);
    return M_PI * r * r;
  }

  double part1 = r1 * r1 * acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
  double part2 = r2 * r2 * acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));
  double part3 =
      0.5 * sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2));

  return part1 + part2 - part3;
}
