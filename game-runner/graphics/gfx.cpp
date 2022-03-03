#include "gfx.h"


vector<float> Object::move(float x, float y) {
    if (x_pos + x >= 0 && x_pos + x < 64) {
        x_pos += x;
    }
    if (x_pos + y >= 0 && x_pos + y < 64) {
        y_pos += y;
    }
    vector<float> ret{x_pos, y_pos};
    return ret;
}

vector<float> Object::getPos() {
    std::vector<float> pos;
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