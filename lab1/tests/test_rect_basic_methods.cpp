#include <cassert>
#include "../src/rect.hpp"

int main() {
    Rect r1;
    assert(r1.get_left() == 0);
    assert(r1.get_right() == 0);
    assert(r1.get_top() == 0);
    assert(r1.get_bottom() == 0);

    Rect r2(1, 5, 6, 2);
    assert(r2.get_left() == 1);
    assert(r2.get_right() == 5);
    assert(r2.get_top() == 6);
    assert(r2.get_bottom() == 2);

    Rect r3(r2);
    assert(r3.get_left() == 1);
    assert(r3.get_right() == 5);
    assert(r3.get_top() == 6);
    assert(r3.get_bottom() == 2);

    r1.set_all(3, 8, 9, 1); 
    assert(r1.get_left() == 3);
    assert(r1.get_right() == 8);
    assert(r1.get_top() == 9);
    assert(r1.get_bottom() == 1);

    assert(r1.get_width() == 5);
    assert(r1.get_height() == 8);

    assert(r1.get_square() == 40);

    r1.set_width(10);
    r1.set_height(15);
    assert(r1.get_right() == r1.get_left() + 10);
    assert(r1.get_bottom() == r1.get_top() - 15);

    return 0;
}