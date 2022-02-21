#ifndef MARPLETILT_GFX_H
#define MARPLETILT_GFX_H

#endif
#include <vector>
#include <algorithm>

using std::vector;


enum draw_type { //TODO try make some way of automatic handling of assets?
    IMAGE,
    MARPLE,
};

class Object {
public:
    static std::vector<Object> instances;

    Object(int x, int y, draw_type shape){
        instances.push_back(*this);
        x_pos = x;
        y_pos = y;
        d_shape = shape;
    }
//    ~Object() {
//        instances.erase(std::remove(instances.begin(), instances.end(), *this), instances.end());
//        delete this;
//    }

    vector<int> getPos();
    vector<int> move(int x, int y);

private:
    draw_type d_shape;
    int x_pos;
    int y_pos;
};

class Marple : public Object {
private:
    int diameter;
public:
    Marple(int x, int y, int d, draw_type shape)
    : Object{x, y, shape}
    {
        diameter = d;
    }
};
