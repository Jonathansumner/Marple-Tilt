#include "collision-boxes.h"
#include "game-objects.h"
#include "loading-bar.h"

StateCollisionBox::StateCollisionBox(int x_pos, int y_pos, int w, int h, int trigger_time, void (*f)(MarpleTiltMachine *, BaseState *), bool loading_bar, MarpleTiltMachine *fsm, BaseState *nS)
{
    stateColliders.push_back(this);
    callback = f;
    StateMachine = fsm;
    NewState = nS;

    x = x_pos;
    y = y_pos;
    width = w;
    height = h;
    progress = 0;
    callback = f;
    progress_secs = trigger_time;
    if (loading_bar)
    {
        bar = new LoadingBar(x, y, height);
    }
    else
    {
        bar = nullptr;
    }
}

void StateCollisionBox::colliderStatePoll(Marple *marple)
{
    for (StateCollisionBox *collider : stateColliders)
    {
        if (checkCollisionTouch(marple, collider))
        {
            if (collider->progress <= (collider->progress_secs * 60) - 1)
            {
                collider->progress++;
            }
            else
            {
                collider->callback(collider->StateMachine, collider->NewState); // if progress bar limit reached, run specific callback
                collider->progress = 0;
                return;
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

bool StateCollisionBox::checkCollision(Marple *marple, StateCollisionBox *collider)
{
    int marp_x = marple->getPos()[0], marp_y = marple->getPos()[1], marp_d = marple->getDiameter();
    if ((((collider->x <= marp_x) && (marp_x <= collider->x + collider->width)) ||
         ((collider->x <= marp_x + marp_d) && (marp_x + marp_d <= collider->x + collider->width))) &&
        (((collider->y <= marp_y) && (marp_y <= collider->y + collider->height)) ||
         ((collider->y <= marp_y + marp_d) && (marp_y + marp_d <= collider->y + collider->height))))
    {
        return true;
    }
    return false; // TODO: look into destructor and removing from vectors
}