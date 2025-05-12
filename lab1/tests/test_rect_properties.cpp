#include <cassert>
#include "../src/rect.hpp"

int main() {
    Rect r(1, 6, 9, 2); // left=1, right=6, top=9, bottom=2
    // width = 5, height = 7

    assert(r.get_width() == 5);
    assert(r.get_height() == 7);
    assert(r.get_square() == 35);

    r.set_width(10);
    assert(r.get_right() == r.get_left() + 10);
    assert(r.get_width() == 10);

    r.set_height(4);
    assert(r.get_bottom() == r.get_top() - 4);  // т.к. top > bottom
    assert(r.get_height() == 4);

    return 0;
}
