#include "rect-functions.h"
#include <cmath>
#include <iostream>

using namespace std;

Rect bounding_rect(Rect r1, Rect r2) {
  int left = min(r1.get_left(), r2.get_left());
  int right = max(r1.get_right(), r2.get_right());
  int top = max(r1.get_top(), r2.get_top());
  int bottom = min(r1.get_bottom(), r2.get_bottom());

  return Rect(left, right, top, bottom);
}

void print_rect(Rect &r) {
	int r_height = abs(r.get_bottom() - r.get_top());
	int r_width = abs(r.get_left() - r.get_right());
	for (int i = 0; i < r_width; ++i) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < r_height - 2; ++i) {
		cout << "#";
		for (int j = 0; j < r_width - 2; ++j) cout << " ";
		cout << "#\n";
	}
	for (int i = 0; i < r_width; ++i) {
		cout << "#";
	}
	cout << endl;
}