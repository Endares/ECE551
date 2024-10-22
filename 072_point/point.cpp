#include "point.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <cmath>

// default constructor
Point::Point() {
  x = 0;
  y = 0;
}

// constructor
Point::Point(double dx, double dy) {
  x = dx;
  y = dy;
}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
}

Point & Point::operator=(const Point & rhs) {
  // check for self-assignment
  if (this != &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
  }
  return *this;
}

// destructor
Point::~Point() {
}
