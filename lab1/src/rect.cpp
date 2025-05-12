#include "rect.hpp"
#include <iostream>
using namespace std;

// Rect::Rect() : left(0), right(0), top(0), bottom(0) {
//     cout << "Вызван Rect(): " << this << endl;
// }
Rect::Rect() : x(0), y(0), width(0), height(0) {
  cout << "Вызван Rect(): " << this << endl;
}

// Rect::Rect(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {
//     cout << "Вызван Rect(int, int, int, int): " << this << endl;
// }
Rect::Rect(int l, int r, int t, int b) : x(l), y(b), width(r - l), height(t - b) {
    cout << "Вызван Rect(int, int, int, int): " << this << endl;
}
// Rect::Rect(const Rect &other) : left(other.left), right(other.right), top(other.top), bottom(other.bottom) {
//         cout << "Вызван Rect(const Rect): " << this << endl;
// }
Rect::Rect(const Rect &other)
    : x(other.x), y(other.y), width(other.width), height(other.height) {
    cout << "Вызван Rect(const Rect): " << this << endl;
}
Rect::~Rect() {
    cout << "Вызван дестркутор класса Rect: ";
    cout << this << endl;
}

// int Rect::get_left() const { return left; }
// int Rect::get_right() const { return right; }
// int Rect::get_top() const { return top; }
// int Rect::get_bottom() const { return bottom; }

int Rect::get_left() const { return x; }
int Rect::get_right() const { return x + width; }
int Rect::get_bottom() const { return y; }
int Rect::get_top() const { return y + height; }

// void Rect::set_all(int left, int right, int top, int bottom) {
//     this->left = left;
//     this->right = right;
//     this->top = top;
//     this->bottom = bottom;
// }

void Rect::set_all(int l, int r, int t, int b) {
  x = l;
  y = b;
  width = r - l;
  height = t - b;
}

// void Rect::inflate(int amount) {
//     left -= amount;
//     right += amount;
//     top += amount;
//     bottom -= amount;
// }

void Rect::inflate(int amount) {
  x -= amount;
  y -= amount;
  width += 2 * amount;
  height += 2 * amount;
}

// void Rect::inflate(int dw, int dh) {
//     left -= dw;
//     right += dw;
//     top += dh;
//     bottom -= dh;
// }

void Rect::inflate(int dw, int dh) {
  x -= dw;
  y -= dh;
  width += 2 * dw;
  height += 2 * dh;
}

// void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
//     left -= d_left;
//     right += d_right;
//     top += d_top;
//     bottom -= d_bottom;
// }

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
  x -= d_left;
  y -= d_bottom;
  width += d_left + d_right;
  height += d_top + d_bottom;
}

// void Rect::move(int dx) {
//     left += dx;
//     right += dx;
// }

void Rect::move(int dx) {
  x += dx;
}

// void Rect::move(int dx, int dy) {
//     left += dx;
//     right += dx;
//     top += dy;
//     bottom += dy;
// }

void Rect::move(int dx, int dy) {
  x += dx;
  y += dy;
}

// int Rect::get_width() const {
//     return right - left;
// }

// int Rect::get_height() const {
//     return bottom - top;
// }

// int Rect::get_square() const {
//     return get_width() * get_height();
// }

int Rect::get_width() const { return width; }
int Rect::get_height() const { return height; }
int Rect::get_square() const { return width * height; }

// void Rect::set_width(int width) {
//     right = left + width;
// }

void Rect::set_width(int w) {
  width = w;
}

// void Rect::set_height(int height) {
//     bottom = top + height;
// }

void Rect::set_height(int h) {
  height = h;
}