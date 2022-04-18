#include "object.h"

using std::vector;

Object::Object(float x, float y, draw_type d_type)
{
    x_pos = x;
    y_pos = y;
    type = d_type;
    red = 255, green = 255, blue = 255;
}

vector<int> Object::getColour()
{
    return {red, green, blue};
}

void Object::clearStage(rgb_matrix::Canvas *c)
{
    c->Clear();
    for (Object *obj : instances)
    {
        delete obj; // delete object pointer (+ run destructor on object)
    }
    instances.clear(); // empty list of all objects
}

void Object::clearRenderBuffer()
{
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            frame_prev[x][y] = nullptr;
            frame[x][y] = nullptr;
        }
    }
}

vector<float> Object::move(float x, float y)
{
    if (x_pos + x >= 0 && x_pos + x < 64)
    {
        x_pos += x;
    }
    if (x_pos + y >= 0 && x_pos + y < 64)
    {
        y_pos += y;
    }
    vector<float> ret{x_pos, y_pos};
    return ret;
}

vector<float> Object::getPos()
{
    std::vector<float> pos;
    pos.push_back(x_pos);
    pos.push_back(y_pos);
    return pos;
}

draw_type Object::getType()
{
    return type;
}

void Object::setColour(std::vector<int> colour)
{
    red = colour[0], green = colour[1], blue = colour[2];
}

void Object::setPos(std::vector<float> pos)
{
    x_pos = pos[0];
    y_pos = pos[1];
}

Object::~Object()
{
}