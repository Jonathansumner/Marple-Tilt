#include "gfx.h"


vector<int> Object::move(int x, int y) {
    if (x_pos + x >= 0 && x_pos + x < 64) {
        x_pos += x;
    }
    if (x_pos + y >= 0 && x_pos + y < 64) {
        y_pos += y;
    }
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

void Object::setColour(std::vector<int> colour) {
    red = colour[0], green = colour[1], blue = colour[2];
}

int Marple::getDiameter() {
    return diameter;
}

int Hole::getDiameter() {
    return diameter;
}