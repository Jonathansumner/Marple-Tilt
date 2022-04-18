#include "textbox.h"
#include "graphics.h"
#include "led-matrix.h"

Textbox::Textbox(float x, float y, const rgb_matrix::Font &f, rgb_matrix::Color tc, rgb_matrix::Canvas *c, const char *txt, rgb_matrix::Color *bg)
    : Object{x, y, TEXT}
{
    instances.push_back(this);
    font = f;
    text_colour = tc;
    text = txt;
    background = bg;
    canvas = c;
}

void Textbox::draw()
{
    rgb_matrix::DrawText(canvas, font, x_pos, y_pos, text_colour, background, text, 0);
}