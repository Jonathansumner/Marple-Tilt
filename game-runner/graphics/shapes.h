#include <cmath>

#ifndef MARPLETILT_SHAPES_H
#define MARPLETILT_SHAPES_H

#endif //MARPLETILT_SHAPES_H

#include "led-matrix.h"
#include "graphics.h"
#include "gfx.h"
using namespace rgb_matrix;

void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]);

void fillBorder(Canvas *c, Color borderColour, int width);