#pragma once
#include <cmath>
#include <limits>

class Point {
private:
  double x;
  double y;
  static double epsilon();

public:
  Point();
  Point(double x, double y);

  double get_x() const;
  double get_y() const;

  void set_x(double new_x);
  void set_y(double new_y);
  void set(double new_x, double new_y);

  bool operator==(const Point &other) const;
  bool operator!=(const Point &other) const;
  bool operator<(const Point &other) const;
  bool operator<=(const Point &other) const;
  bool operator>(const Point &other) const;
  bool operator>=(const Point &other) const;
};
