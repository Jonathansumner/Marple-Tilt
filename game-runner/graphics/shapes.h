#include <cmath>

#ifndef MARPLETILT_SHAPES_H
#define MARPLETILT_SHAPES_H

#endif //MARPLETILT_SHAPES_H
#pragma once

#include "led-matrix.h"
#include "graphics.h"
#include "gfx.h"
#include "../FSM/MarpleTiltMachine.h"

void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]);

void fillBorder(rgb_matrix::Canvas *c, rgb_matrix::Color borderColour, int width);

void arrowButton(bool direction);

class CollisionBox {
protected:
    int x, y;
    int width;
    int height;
    int progress;
    int progress_secs;
    void (*callback) ();
    LoadingBar * bar;
    static bool checkCollision(Marple * marple, CollisionBox * collider);
    static std::vector<CollisionBox *> colliders; //TODO: make an Object instead? or keep separate track
public:
    CollisionBox(int x, int y, int w, int h, int progress_secs, void (*func)(), bool loading_bar);
    static void colliderPoll(Marple * marple);
};

class StateCollisionBox : public CollisionBox {
    private:
        void (*callback)(MarpleTiltMachine*, GameState*);
        MarpleTiltMachine* StateMachine;
        GameState *NewState;

    public:
        StateCollisionBox(int x, int y, int w, int h, int progress_secs, void (*f)(MarpleTiltMachine*, GameState*), bool loading_bar, MarpleTiltMachine* fsm, GameState *nS);
};

class MapCollisionBox : public CollisionBox {
    private:
        void (*callback) (MapMenu*, int);
        MapMenu *mmState;
        int mapID;

    public:
        MapCollisionBox(int x, int y, int w, int h, int progress_secs, void (*f) (MapMenu*, int), bool loading_bar, MapMenu *mm, int ID);
};