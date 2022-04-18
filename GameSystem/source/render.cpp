#include "render.h"
#include "game-objects.h"
#include "collision-boxes.h"

#include <math.h>

using rgb_matrix::Color;
using rgb_matrix::Canvas;

void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64])
{
    int starting_x = (int)std::round(start_x);
    int starting_y = (int)std::round(start_y);
    for (int w_curr = 0; w_curr < w; w_curr++)
    {
        for (int h_curr = 0; h_curr < h; h_curr++)
        {
            if ((starting_x + w_curr <= 64) && (starting_x + w_curr >= 0) and (starting_y + h_curr <= 64) &&
                (starting_y + h_curr >= 0))
            {
                array[starting_x + w_curr][starting_y + h_curr] = obj;
            }
        }
    }
}

void fillBorder(Color borderColor, int width)
{
    Wall *walls[124];
    int rVal = static_cast<int>(borderColor.r),
        gVal = static_cast<int>(borderColor.g),
        bVal = static_cast<int>(borderColor.b);

    for (int i = 0; i < 31; i++)
    {
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

void ColliderCheck(Marple *marple)
{
    CollisionBox::colliderPoll(marple);
    StateCollisionBox::colliderStatePoll(marple);
}

void clearAll(Canvas *c)
{
    Object::clearRenderBuffer();
    Object::clearStage(c);
    CollisionBox::clear();
    StateCollisionBox::clear();
}