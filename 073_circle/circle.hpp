#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  // default constructor
  Circle();
  // for const radius, a initializer list is a MUST
  Circle(Point p, const double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
  double circleIntersectionArea(double r1, double r2, double d);
};
