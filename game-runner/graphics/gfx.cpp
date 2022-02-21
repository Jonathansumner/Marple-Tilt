#include "gfx.h"

vector<int> Object::move(int x, int y) {
    x_pos += x;
    y_pos += y;
    vector<int> ret{x_pos, y_pos};
    return ret;
}

vector<int> Object::getPos() {
    std::vector<int> pos;
    pos.push_back(x_pos);
    pos.push_back(y_pos);
    return pos;
}

draw_type Object::getType() {
    return type;
}

int Marple::getDiameter() {
    return diameter;
}