#pragma once
#include "object.h"
#include "led-matrix.h"
#include "graphics.h"

class Textbox : public Object
{
protected:
    rgb_matrix::Font font;
    rgb_matrix::Color text_colour;
    const char *text;
    rgb_matrix::Color *background;
    rgb_matrix::Canvas *canvas;

public:
    Textbox(float x, float y, const rgb_matrix::Font &f, rgb_matrix::Color tc, rgb_matrix::Canvas *c, const char *txt, rgb_matrix::Color *bg = nullptr);
    void draw();
};