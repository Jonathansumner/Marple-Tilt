#pragma once
#include "led-matrix.h"
#include "graphics.h"

class Marple;
class Object;

void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]);

void fillBorder(rgb_matrix::Color borderColour, int width);

void ColliderCheck(Marple * marple);

void clearAll(rgb_matrix::Canvas *c);

void update(rgb_matrix::Canvas *c, bool clear = false);

void render(rgb_matrix::Canvas *canvas);