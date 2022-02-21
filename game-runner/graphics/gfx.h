#ifndef MARPLETILT_GFX_H
#define MARPLETILT_GFX_H

#endif
#include <vector>
#include <algorithm>

using std::vector;


enum draw_type { //TODO try make some way of automatic handling of assets?
    IMAGE,
    MARPLE,
    HOLE
};

class Object {
public:
    static std::vector<Object*> instances;

    Object(int x, int y, draw_type d_type){
        x_pos = x;
        y_pos = y;
        type = d_type;
    }
//    ~Object() {
//        instances.erase(std::remove(instances.begin(), instances.end(), *this), instances.end());
//        delete this;
//    }

    virtual vector<int> getPos();
    draw_type getType();
    vector<int> move(int x, int y);

private:
    draw_type type;
    int x_pos;
    int y_pos;
};

class Marple : public Object {
private:
    int diameter;
public:
    Marple(int x, int y, int d)
    : Object{x, y, MARPLE}
    {
        instances.push_back(this);
        diameter = d;
    }
    int getDiameter();
};

class Hole : public Object {
private:
    int diameter;
public:
    Hole(int x, int y, int d)
            : Object{x, y, HOLE}
    {
        instances.push_back(this);
        diameter = d;
    }
    int getDiameter();
};