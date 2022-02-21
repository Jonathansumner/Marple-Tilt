#include "gfx.h"

vector<int> Object::move(int x, int y) {
    x_pos += x;
    y_pos += y;
    vector<int> ret{x_pos, y_pos};
    return ret;
}