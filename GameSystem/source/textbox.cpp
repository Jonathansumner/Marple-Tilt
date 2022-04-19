#include "textbox.h"
#include "graphics.h"
#include "led-matrix.h"

#include <string.h>

Textbox::Textbox(float x, float y, std::vector<int> rgb, rgb_matrix::Canvas *c, std::string txt, rgb_matrix::Color *bg)
    : Object{x, y, TEXT}
{
    instances.push_back(this);
    font.LoadFont("img/5x8.bdf");

    text_colour = new rgb_matrix::Color(rgb[0], rgb[1], rgb[2]);

    text = new char[txt.length() + 1];
    strcpy(text, txt.c_str());

    background_colour = bg;
    canvas = c;
}

Textbox::~Textbox()
{
    delete text_colour;
    delete text;
    delete background_colour;
}

void Textbox::draw()
{
    rgb_matrix::DrawText(canvas, font, x_pos, y_pos, *text_colour, background_colour, text, 0);
}