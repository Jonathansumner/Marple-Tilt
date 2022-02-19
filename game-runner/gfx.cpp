#include "gfx.h"
#include <vector>

using std::vector;

Object::Object(int x, int y, draw_type shape) {
    x_pos = x;
    y_pos = y;
}

vector<int> Object::move(int x, int y) {
    x_pos+=x;
    y_pos+=y;
    vector<int> ret{x_pos, y_pos};
    return ret;
}
