#include "point.hpp"

double Point::epsilon() {
  // Машинный эпсилон, умноженный для устойчивости сравнения
  return std::numeric_limits<double>::epsilon() * 100;
}

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}

double Point::get_x() const { return x; }

double Point::get_y() const { return y; }

void Point::set_x(double new_x) { x = new_x; }

void Point::set_y(double new_y) { y = new_y; }

void Point::set(double new_x, double new_y) {
  x = new_x;
  y = new_y;
}

bool Point::operator==(const Point &other) const {
  return std::fabs(x - other.x) < epsilon() && std::fabs(y - other.y) < epsilon();
}

bool Point::operator!=(const Point &other) const {
  return !(*this == other);
}

bool Point::operator<(const Point &other) const {
  if (std::fabs(x - other.x) >= epsilon())
    return x < other.x;
  return y < other.y - epsilon();
}

bool Point::operator<=(const Point &other) const {
  return (*this < other) || (*this == other);
}

bool Point::operator>(const Point &other) const {
  return !(*this <= other);
}

bool Point::operator>=(const Point &other) const {
  return !(*this < other);
}
