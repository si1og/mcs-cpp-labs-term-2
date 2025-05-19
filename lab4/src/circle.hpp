#pragma once
#include "point.hpp"

class Circle {
private:
    Point center;
    double radius;

public:
    Circle();

    Circle(const Point& center, double radius);

    const Point& get_center() const;
    double get_radius() const;

    void set_center(const Point& new_center);
    void set_radius(double new_radius);

    double area() const;
    double circumference() const;
};
