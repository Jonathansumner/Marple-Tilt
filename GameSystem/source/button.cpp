#include "button.h"
#include "collision-box.h"
#include "loading-bar.h"

int Button::getWidth()
{
    return width;
}

int Button::getHeight()
{
    return height;
}

char *Button::getPath()
{
    return path;
}

float Button::getBarWidth()
{
    return box->getBar()->getDiameter();
}