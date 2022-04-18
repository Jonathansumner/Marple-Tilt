#include <math.h>

#include "collision-box.h"
#include "loading-bar.h"
#include "game-objects.h"

CollisionBox::CollisionBox(int x_pos, int y_pos, int w, int h, int trigger_time, void (*func)(Marple *marple), bool loading_bar, bool touch_trig)
{ //
    Colliders.push_back(this);
    x = x_pos;
    y = y_pos;
    width = w;
    height = h;
    progress = 0;
    callback = func;
    progress_secs = trigger_time;
    trigger_type = touch_trig;
    if (loading_bar)
    {
        bar = new LoadingBar(x, y, height);
    }
    else
    {
        bar = nullptr;
    }
}

bool CollisionBox::checkCollisionTouch(Marple *marple, CollisionBox *collider)
{
    int marp_x = (int)std::round(marple->getPos()[0]), marp_y = (int)std::round(marple->getPos()[1]), marp_d = marple->getDiameter();
    if ((((collider->x <= marp_x) && (marp_x <= collider->x + collider->width)) ||
         ((collider->x <= marp_x + marp_d) && (marp_x + marp_d <= collider->x + collider->width))) &&
        (((collider->y <= marp_y) && (marp_y <= collider->y + collider->height)) ||
         ((collider->y <= marp_y + marp_d) && (marp_y + marp_d <= collider->y + collider->height))))
    {
        return true;
    }
    return false; // TODO: look into destructor and removing from vectors
}

bool CollisionBox::checkCollisionProx(Marple *marple, CollisionBox *collider, double threshold)
{
    int marp_d = marple->getDiameter();
    auto marp_x = marple->getPos()[0], marp_y = marple->getPos()[1];
    auto col_x = collider->getX(), col_y = collider->getY(),
         col_w = collider->getWidth(), col_h = collider->getHeight();
    double centre_x = col_x + col_w / 2, centre_y = col_y + col_h / 2;
    double m_centre_x = marp_x + marp_d / 2, m_centre_y = marp_y + marp_d / 2;
    double dist = sqrt(pow((centre_x - m_centre_x), 2) + pow((centre_y - m_centre_y), 2)); // think abs is not necessary
    if (dist <= threshold)
    {
        return true;
    }
    return false;
}

void CollisionBox::colliderPoll(Marple *marple)
{ // TODO: make real-time?
    for (CollisionBox *collider : Colliders)
    {
        if ((checkCollisionTouch(marple, collider) && collider->trigger_type) or // check based on which trigger type
            (checkCollisionProx(marple, collider) && !collider->trigger_type))
        {
            if (collider->progress <= (collider->progress_secs * 60) - 1)
            {
                collider->progress++;
            }
            else
            {
                collider->callback(marple); // if progress bar limit reached, run specific callback
                collider->progress = 0;
            }
        }
        else
        {
            collider->progress = 0;
        }
        if (collider->bar)
        {
            collider->bar->setDiameter(collider->progress * ((float)collider->width / (float)(collider->progress_secs * 60)));
        }
    }
}

LoadingBar *CollisionBox::getBar()
{
    if (bar)
    {
        return bar;
    }
    return nullptr;
}

int CollisionBox::getWidth()
{
    return width;
}

int CollisionBox::getHeight()
{
    return height;
}

int CollisionBox::getX()
{
    return x;
}

int CollisionBox::getY()
{
    return y;
}