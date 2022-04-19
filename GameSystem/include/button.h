#pragma once
#include "object.h"

#include <string.h>

class CollisionBox;

class Button : public Object
{
protected:
    char *path;
    CollisionBox *box;

public:
    int width;
    int height;
    Button(int x_pos, int y_pos, int w, int h, std::string p, int time = 1);
    ~Button();

    int getWidth();
    int getHeight();
    float getBarWidth();
    char *getPath();
};