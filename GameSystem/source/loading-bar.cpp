#include "loading-bar.h"

LoadingBar::LoadingBar(float x_pos, float y_pos, int h)
    : Object{x_pos, y_pos, BAR}
{
    instances.push_back(this);
    diameter = 0;
    height = h;
}

void LoadingBar::setDiameter(float d)
{
    diameter = d;
}

float LoadingBar::getDiameter()
{
    return diameter;
}

int LoadingBar::getHeight()
{
    return height;
}