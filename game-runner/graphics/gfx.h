#ifndef MARPLETILT_GFX_H
#define MARPLETILT_GFX_H

#endif

#include <vector>
#include <algorithm>
#pragma once
using std::vector;


enum draw_type { //TODO try make some way of automatic handling of assets?
    MARPLE,
    HOLE,
    WALL
};

class Object {
public:
    int red, green, blue;
    static std::vector<Object*> instances;

    Object(float x, float y, draw_type d_type){
        x_pos = x;
        y_pos = y;
        type = d_type;
        red = 255, green = 255, blue = 255;
    }

    virtual void setColour(std::vector<int> colour);
    virtual vector<float> getPos();
    virtual draw_type getType();
    virtual vector<float> move(float x, float y);

private:
    draw_type type;
    float x_pos;
    float y_pos;
};

class Marple : public Object {
private:
    int diameter;
public:
    Marple(float x, float y, int d)
    : Object{x, y, MARPLE}
    {
        instances.push_back(this);
        diameter = d;
        x_velocity = 0;
        y_velocity = 0;
    }
    int getDiameter();

    float x_velocity;
    float y_velocity;
    float x_acceleration;
    float y_acceleration;
};

class Hole : public Object {
private:
    int diameter;
public:
    Hole(float x, float y, int d)
            : Object{x, y, HOLE}
    {
        instances.push_back(this);
        diameter = d;
    }
    int getDiameter();
};

class Wall : public Object {
public:
    int diameter;
    Wall(float x, float y, int d)
            : Object{x, y, WALL}
    {
        instances.push_back(this);
        diameter = d;
    }
};