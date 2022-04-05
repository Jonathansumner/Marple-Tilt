#include <cmath>

#ifndef MARPLETILT_SHAPES_H
#define MARPLETILT_SHAPES_H

#endif //MARPLETILT_SHAPES_H
#pragma once

#include "led-matrix.h"
#include "graphics.h"
#include "gfx.h"
using namespace rgb_matrix;

void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]);

void fillBorder(Canvas *c, Color borderColour, int width);

class CollisionBox {
public:
    int x, y;
    int width;
    int height;
    int progress;
    int progress_secs;
    void (*callback)();
public:
    static std::vector<CollisionBox *> colliders; //TODO: make an Object instead? or keep separate track
    CollisionBox(int x, int y, int w, int h, int progress_secs, void (*func)());
    static void colliderPoll(Marple * marple);
    static bool checkCollision(Marple * marple, CollisionBox * collider);
};
