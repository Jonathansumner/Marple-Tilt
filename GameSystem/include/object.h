#pragma once

#include "led-matrix.h"
#include <vector>

// Order of enum ordinal determines drawing order, and therefore the drawing layer priority
enum draw_type
{
    TEXT,
    MARPLE,
    HOLE,
    WALL,
    HOME,
    END,
    BAR,
    BUTTON,
};

class Object
{
public:
    int red, green, blue;
    static std::vector<Object *> instances;

    static Object *frame_prev[64][64];
    static Object *frame[64][64];

    Object(float x, float y, draw_type d_type);
    ~Object();

    virtual void setColour(std::vector<int> colour);
    virtual std::vector<int> getColour();
    virtual std::vector<float> getPos();
    virtual draw_type getType();
    virtual std::vector<float> move(float x, float y);
    virtual void setPos(std::vector<float> pos);

    static void clearStage(rgb_matrix::Canvas *c);

    static void clearRenderBuffer();

protected:
    draw_type type;
    float x_pos;
    float y_pos;
};