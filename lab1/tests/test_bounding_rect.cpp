#include <cassert>
#include "../src/rect-functions.h"

int main() {
    Rect a(1, 5, 6, 2);
    Rect b(3, 8, 7, 1);
    Rect result = bounding_rect(a, b);

    assert(result.get_left() == 1);
    assert(result.get_right() == 8);
    assert(result.get_top() == 7);
    assert(result.get_bottom() == 1);

    Rect c(8, 3, 7, 1);
    Rect d(2, 6, 5, 2);

    Rect bound = bounding_rect(c, d);

    assert(bound.get_left() == 2 || bound.get_left() == 3);
    assert(bound.get_right() == 8 || bound.get_right() == 6);
    assert(bound.get_top() == 7 || bound.get_top() == 5);
    assert(bound.get_bottom() == 1 || bound.get_bottom() == 2);

    return 0;
}