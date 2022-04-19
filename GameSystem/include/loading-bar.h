#pragma once
#include "object.h"

class LoadingBar : public Object
{
public:
    float diameter;
    int height;
    void setDiameter(float d);

public:
    float getDiameter();
    int getHeight();
    LoadingBar(float x_pos, float y_pos, int h);
};