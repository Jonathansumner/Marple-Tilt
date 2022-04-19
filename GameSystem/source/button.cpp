#include "button.h"
#include "collision-box.h"
#include "loading-bar.h"

Button::Button(int x_pos, int y_pos, int w, int h, std::string p, int time)
    : Object{(float)x_pos, (float)y_pos, BUTTON}
{
    width = w;
    height = h;
    instances.push_back(this);
    path = new char[p.length() + 1];
    strcpy(path, p.c_str());
}

Button::~Button()
{
    delete path;
}

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