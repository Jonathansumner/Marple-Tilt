#pragma once
#include "object.h"

class CollisionBox;

class Button : public Object
{
protected:
    char *path;
    CollisionBox *box;

public:
    int width;
    int height;
    Button(int x_pos, int y_pos, int w, int h, char *p, int time = 2)
        : Object{(float)x_pos, (float)y_pos, BUTTON}
    {
        width = w;
        height = h;
        instances.push_back(this);
        path = p;
    }
    int getWidth();
    int getHeight();
    float getBarWidth();
    char *getPath();
};