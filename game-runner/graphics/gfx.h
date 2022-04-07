#ifndef MARPLETILT_GFX_H
#define MARPLETILT_GFX_H
#endif

#pragma once

#include <vector>
#include <algorithm>
#include <graphics.h>
#include <cmath>
#include "led-matrix.h"
#include "../FSM/MarpleTiltMachine.h"

using namespace rgb_matrix;
using std::vector;

enum draw_type { //TODO try make some way of automatic handling of assets?
    MARPLE,
    HOLE,
    WALL,
    BAR,
    BUTTON
};

class MapMenu;
class MarpleTiltMachine;

class Object
{
public:
    int red, green, blue;
    static std::vector<Object *> instances;

    static Object *frame_prev[64][64];
    static Object *frame[64][64];

    Object(float x, float y, draw_type d_type)
    {
        x_pos = x;
        y_pos = y;
        type = d_type;
        red = 255, green = 255, blue = 255;
    }

    virtual void setColour(std::vector<int> colour);
    virtual vector<float> getPos();
    virtual draw_type getType();
    virtual vector<float> move(float x, float y);
    virtual void setPos(std::vector<float> pos);

private:
    draw_type type;
    float x_pos;
    float y_pos;
};

class Marple : public Object {
private:
    int diameter;
public:
    Marple(float x, float y, int d)
    : Object{x, y, MARPLE}
    {
        instances.push_back(this);
        diameter = d;
        x_velocity = 0;
        y_velocity = 0;
        x_acceleration = 0;
        y_acceleration = 0;
    }

    ~Marple();

    int getDiameter();

    float x_velocity;
    float y_velocity;
    float x_acceleration;
    float y_acceleration;
};

class Hole : public Object {
private:
    int diameter;
public:
    Hole(float x, float y, int d)
            : Object{x, y, HOLE}
    {
        instances.push_back(this);
        diameter = d;
    }
    int getDiameter();
};

class Wall : public Object {
public:
    int diameter;
    Wall(float x, float y, int d)
            : Object{x, y, WALL}
    {
        instances.push_back(this);
        diameter = d;
    }
};

class LoadingBar : public Object {
public:
    float diameter;
    int height;
    void setDiameter(float d);

public:
    float getDiameter();
    int getHeight();
    LoadingBar(float x_pos, float y_pos, int h)
        : Object{x_pos, y_pos, BAR}
    {
        instances.push_back(this);
        diameter = 0;
        height = h;
    }
};

class CollisionBox {
protected:
    int x, y;
    int width;
    int height;
    int progress;
    int progress_secs;
    void (*callback)();
    LoadingBar * bar;
    static bool checkCollision(Marple * marple, CollisionBox * collider);
    static std::vector<CollisionBox *> colliders; //TODO: make an Object instead? or keep separate track
public:
    CollisionBox(int x, int y, int w, int h, int progress_secs, void (*func)(), bool loading_bar=true);
    static void colliderPoll(Marple * marple);
    LoadingBar* getBar();
};

class StateCollisionBox : public CollisionBox
{
public:
    void (*callback)(MarpleTiltMachine *, GameState *);
    MarpleTiltMachine *StateMachine;
    GameState *NewState;
    static std::vector<StateCollisionBox *> stateColliders;

    StateCollisionBox(int x, int y, int w, int h, int progress_secs, void (*f)(MarpleTiltMachine *, GameState *), bool loading_bar, MarpleTiltMachine *fsm, GameState *nS);
    static void colliderStatePoll(Marple * marple);
    static bool checkCollision(Marple *marple, StateCollisionBox *collider);
};

class MapCollisionBox : public CollisionBox
{
private:
    void (*callback)(MapMenu *, int);
    MapMenu *mmState;
    int mapID;

public:
    MapCollisionBox(int x, int y, int w, int h, int progress_secs, void (*f)(MapMenu *, int), bool loading_bar, MapMenu *mm, int ID);
};

class Button : public Object {
protected:
    char * path;
    CollisionBox * box;
public:
    int width;
    int height;
    Button(int x_pos, int y_pos, int w, int h, char * p, int time=2)
            : Object{(float)x_pos, (float)y_pos, BUTTON}
    {
        width = w;
        height = h;
        instances.push_back(this);
        path = p;
    }
    int getWidth();
    int getHeight();
    float getBarWidth();
    char * getPath();
};

class StateButton : public Button {
    private:
        
    public:
        StateButton(int xp, int yp, int w, int h, char *p, void(*f)(MarpleTiltMachine*, GameState*), MarpleTiltMachine *fsm, GameState *ns, int time=2);

};

//OLD SHAPES

void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]);

void fillBorder(Canvas *c, Color borderColour, int width);