#include <cmath>
#include "gfx.h"
#include "shapes.h"
#include "iostream"

void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]) {
    int starting_x = (int) std::round(start_x);
    int starting_y = (int) std::round(start_y);
    for (int w_curr = 0; w_curr < w; w_curr++) {
        for (int h_curr = 0; h_curr < h; h_curr++) {
            if ((starting_x + w_curr <= 64) && (starting_x + w_curr >= 0) and (starting_y + h_curr <= 64) &&
                (starting_y + h_curr >= 0)) {
                array[starting_x + w_curr][starting_y + h_curr] = obj;
            }
        }
    }
}

void fillBorder(Canvas *c, Color borderColor, int width) {
    Wall *walls[124];
    int rVal = static_cast<int>(borderColor.r),
            gVal = static_cast<int>(borderColor.g),
            bVal = static_cast<int>(borderColor.b);

    for (int i = 0; i < 31; i++) {
        float n = static_cast<float>(i);

        walls[i] = new Wall(n * 2, 0, width);
        walls[i]->setColour({rVal, gVal, bVal});

        walls[i + 31] = new Wall(62, n * 2, width);
        walls[i + 31]->setColour({rVal, gVal, bVal});

        walls[i + 62] = new Wall(62 - n * 2, 62, width);
        walls[i + 62]->setColour({rVal, gVal, bVal});

        walls[i + 93] = new Wall(0, 62 - n * 2, width);
        walls[i + 93]->setColour({rVal, gVal, bVal});
    }
}

CollisionBox::CollisionBox(int x_pos, int y_pos, int w, int h, int trigger_time, void (*func)()) { //
    colliders.push_back(this);
    x = x_pos;
    y = y_pos;
    width = w;
    height = h;
    progress = 0;
    callback = func;
    progress_secs = trigger_time;
}

bool CollisionBox::checkCollision(Marple *marple, CollisionBox *collider) {
    int marp_x = marple->getPos()[0], marp_y = marple->getPos()[1], marp_d = marple->getDiameter();
    if ((((collider->x <= marp_x) && (marp_x <= collider->x + collider->width)) ||
        ((collider->x <= marp_x + marp_d) && (marp_x + marp_d <= collider->x + collider->width)))
        &&
        (((collider->y <= marp_y) && (marp_y <= collider->y + collider->height)) ||
        ((collider->y <= marp_y + marp_d) && (marp_y + marp_d <= collider->y + collider->height)))) {
        return true;
    }
    return false; //TODO: look into destructor and removing from vectors
}

void CollisionBox::colliderPoll(Marple *marple) { //TODO: make real-time?
    for (CollisionBox *collider: colliders) {
        if (checkCollision(marple, collider)) {
            if (collider->progress <= (collider->progress_secs * 60) - 1) {
                collider->progress++;
            } else {
                collider->callback(); // if progress bar limit reached, run specific callback
            }
        } else {
            collider->progress = 0;
        }
    }
}
