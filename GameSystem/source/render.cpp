#include "render.h"
#include "game-objects.h"
#include "collision-boxes.h"
#include "textbox.h"
#include "button.h"
#include "images.h"

#include <math.h>
#include <vector>
#include <cstring>
#include <algorithm>

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

void update(Canvas *c, bool clear)
{ // Update object references within the render buffer
    std::sort(Object::instances.begin(), Object::instances.end(),
         [](Object *cmp1, Object *cmp2)
         { return cmp1->getType() > cmp2->getType(); });
    if (clear)
        memcpy(Object::frame_prev, Object::frame, sizeof(Object::frame_prev));
    for (Object *obj : Object::instances)
    {
        if (obj)
        {
            switch (obj->getType())
            {
            case MARPLE:
            {
                int d = dynamic_cast<Marple *>(obj)->getDiameter();
                Marple *ref;
                if (!clear)
                {
                    ref = dynamic_cast<Marple *>(obj);
                }
                else
                {
                    ref = nullptr;
                }
                fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                break;
            }
            case HOLE:
            {
                int d = dynamic_cast<Hole *>(obj)->getDiameter();
                auto *ref = dynamic_cast<Hole *>(obj);
                fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                break;
            }
            case WALL:
            {
                int d = dynamic_cast<Wall *>(obj)->diameter;
                auto *ref = dynamic_cast<Wall *>(obj);
                fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                break;
            }
            case TEXT:
            {
                dynamic_cast<Textbox *>(obj)->draw();
                break;
            }
            case END:
            {
                int d = dynamic_cast<End *>(obj)->getDiameter();
                auto *ref = dynamic_cast<End *>(obj);
                fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                break;
            }
            case HOME:
            {
                int d = dynamic_cast<Home *>(obj)->getDiameter();
                auto *ref = dynamic_cast<Home *>(obj);
                fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
            }
            case BUTTON:
            {
                auto *button = dynamic_cast<Button *>(obj);
                int d = std::round(button->getBarWidth());
                int h = button->getHeight();
                Button *ref;
                if (!clear)
                {
                    ref = button;
                }
                else
                {
                    ref = nullptr;
                }
                if (ref)
                {
                    drawImage(button->getPath(), c,
                              {(int)button->getPos()[0], (int)button->getPos()[1], button->getWidth(),
                               button->getHeight()});
                }
                fillRect(obj->getPos()[0], obj->getPos()[1], d, h, ref, Object::frame);
                break;
            }
            case BAR:
                break;
            }
        }
    }
}

void render(Canvas *canvas)
{ // render each pixel with respect to the object reference
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (Object::frame[i][j] && !Object::frame_prev[i][j])
            {
                canvas->SetPixel(i, j, Object::frame[i][j]->red, Object::frame[i][j]->green, Object::frame[i][j]->blue);
            }
            else if (!Object::frame[i][j] && Object::frame_prev[i][j])
            {
                canvas->SetPixel(i, j, 0, 0, 0);
            }
        }
    }
}