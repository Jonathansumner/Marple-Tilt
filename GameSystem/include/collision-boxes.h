#pragma once
#include "collision-box.h"

class MarpleTiltMachine;
class BaseState;

class StateCollisionBox : public CollisionBox
{
public:
    void (*callback)(MarpleTiltMachine *, BaseState *);
    MarpleTiltMachine *StateMachine;
    BaseState *NewState;
    static std::vector<StateCollisionBox *> stateColliders;

    StateCollisionBox(int x, int y, int w, int h, int progress_secs, void (*f)(MarpleTiltMachine *, BaseState *), bool loading_bar, MarpleTiltMachine *fsm, BaseState *nS);
    static void colliderStatePoll(Marple *marple);
    static bool checkCollision(Marple *marple, StateCollisionBox *collider);
    static void clear()
    {
        stateColliders.clear();
    }
};