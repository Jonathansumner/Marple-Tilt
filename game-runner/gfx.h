#ifndef MARPLETILT_GFX_H
#define MARPLETILT_GFX_H

#endif
#include <vector>

using std::vector;

enum draw_type {
    IMAGE,
    MARPLE_2x2,
    MARPLE_4x4,
    MARPLE_8x8
};

class Object {
public:
    Object(int x, int y, draw_type shape);
    vector<int> move(int x, int y);
private:
    draw_type shape;
    int x_pos;
    int y_pos;
};
