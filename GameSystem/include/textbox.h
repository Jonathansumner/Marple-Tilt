#pragma once
#include "object.h"
#include "led-matrix.h"
#include "graphics.h"

#include <string>
#include <vector>

class Textbox : public Object
{
protected:
    rgb_matrix::Font font;
    rgb_matrix::Color *text_colour;
    char *text;
    rgb_matrix::Color *background_colour;
    rgb_matrix::Canvas *canvas;

public:
    Textbox(float x, float y, std::vector<int> rgb, rgb_matrix::Canvas *c, std::string txt, rgb_matrix::Color *bg = NULL);
    ~Textbox();
    void draw();
};