#include <cassert>
#include "../src/rect.hpp"

int main() {
    Rect r(1, 5, 6, 2);  // left=1, right=5, top=6, bottom=2

    // move(dx)
    r.move(2);  // left=3, right=7
    assert(r.get_left() == 3);
    assert(r.get_right() == 7);
    assert(r.get_top() == 6);
    assert(r.get_bottom() == 2);

    // move(dx, dy)
    r.move(-1, 3);  // left=2, right=6, top=9, bottom=5
    assert(r.get_left() == 2);
    assert(r.get_top() == 9);
    assert(r.get_bottom() == 5);

    // inflate(int amount)
    r.set_all(2, 6, 10, 3);  // left=2, right=6, top=10, bottom=3
    r.inflate(1);  // left=1, right=7, top=11, bottom=2
    assert(r.get_left() == 1);
    assert(r.get_right() == 7);
    assert(r.get_top() == 11);
    assert(r.get_bottom() == 2);

    // inflate(dw, dh)
    r.inflate(1, 2);  // left=0, right=8, top=13, bottom=0
    assert(r.get_top() == 13);
    assert(r.get_bottom() == 0);

    // inflate(d_left, d_right, d_top, d_bottom)
    r.inflate(2, 1, 2, 1);  // left=-2, right=9, top=15, bottom=-1
    assert(r.get_left() == -2);
    assert(r.get_bottom() == -1);
    assert(r.get_top() == 15);

    return 0;
}
