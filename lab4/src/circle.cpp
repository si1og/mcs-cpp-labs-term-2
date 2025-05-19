#include "circle.hpp"
#include <cmath>

Circle::Circle() : center(0, 0), radius(0) {}

Circle::Circle(const Point& center, double radius) : center(center), radius(radius) {}

const Point& Circle::get_center() const {
  return center;
}

double Circle::get_radius() const {
  return radius;
}

void Circle::set_center(const Point& new_center) {
  center = new_center;
}

void Circle::set_radius(double new_radius) {
  radius = new_radius;
}

double Circle::area() const {
  return M_PI * radius * radius;
}

double Circle::circumference() const {
  return 2 * M_PI * radius;
}
