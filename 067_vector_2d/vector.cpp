#include "vector.hpp"

#include <cmath>
#include <cstdio>
using std::sqrt;

/* write your class implementation in this file
 */
/*This function initializes x and y to be the arguments passed in.*/
void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}
/*This function returns the magnitude of the vector from the origin
  (0, 0) to (x, y).*/

double Vector2D::getMagnitude() const {
  return sqrt(pow(x, 2) + pow(y, 2));
}

/*The overloaded + operator should do vector addition in the usual way and return a copy of the new vector.*/
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D res;
  res.x = x + rhs.x;
  res.y = y + rhs.y;
  return res;
}

/*The overloaded += operator should add the lhs and rhs vector and
    assign the result to the object pointed to by this*/
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

/*This function performs the dot product operation,
    returning a double x1 *x2 + y1 *y2.*/
double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}

/*This function should print the vector in the format<% .2f, % .2f>,
    giving the x and y values.*/
void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
