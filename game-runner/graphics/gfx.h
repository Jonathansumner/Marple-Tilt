#ifndef MARPLETILT_GFX_H
#define MARPLETILT_GFX_H
#endif

#pragma once

#include <vector>
#include <algorithm>
#include <graphics.h>
#include <cmath>
#include "led-matrix.h"

using namespace rgb_matrix;
using std::vector;

enum draw_type { //TODO try make some way of automatic handling of assets?
    MARPLE,
    HOLE,
    WALL,
    BAR,
    BUTTON,
    HOME,
};

class MapMenu;
class MarpleTiltMachine;
class GameState;

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

class Home : public Object {
private:
    int diameter;
public:
    Home(float x, float y, int d)
            : Object{x, y, HOME}
    {
        diameter = d;
    }
    float getX();
    float getY();
};

class Marple : public Object {
private:
    int diameter;
    Home * home;
public:
    Marple(float x, float y, int d, Home * h)
    : Object{x, y, MARPLE}
    {
        instances.push_back(this);
        diameter = d;
        x_velocity = 0;
        y_velocity = 0;
        x_acceleration = 0;
        y_acceleration = 0;
        home = h;
    }

    ~Marple();

    int getDiameter();
    void returnHome();
    static void returnWrapper(Marple * m);
    float x_velocity;
    float y_velocity;
    float x_acceleration;
    float y_acceleration;
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
    void (*callback)(Marple * marple);
    bool trigger_type; // trigger_type = true : touch trigger | trigger_type = false : proximity trigger

    static bool checkCollisionTouch(Marple * marple, CollisionBox * collider);
    static bool checkCollisionProx(Marple *marple, CollisionBox *collider, double threshold = 1);
    static std::vector<CollisionBox *> Colliders; //TODO: make an Object instead? or keep separate track
public:
    CollisionBox(int x, int y, int w, int h, int progress_secs, void (*func)(Marple * marple), bool loading_bar=true, bool touch_trig = true);
    static void colliderPoll(Marple * marple);
    LoadingBar* getBar();
    LoadingBar * bar;
    int getWidth();
    int getHeight();
    int getX();
    int getY();
};


class Hole : public Object {
private:
    int diameter;
    CollisionBox *box;
public:
    Hole(float x, float y, int d, Marple * marple)
            : Object{x, y, HOLE}
    {
        instances.push_back(this);
        diameter = d;
        box = new CollisionBox(x, y, d, d, 0, &Marple::returnWrapper, false, false);
    }
    int getDiameter();
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
    static std::vector<MapCollisionBox*> mapColliders;

public:
    MapCollisionBox(int x, int y, int w, int h, int progress_secs, void (*f)(MapMenu *, int), bool loading_bar, MapMenu *mm, int ID);
    static void colliderMapPoll(Marple* marple);
    static bool checkCollision(Marple* marple, MapCollisionBox *collider);
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

class MapButton : public Button
{
private:
public:
    MapButton(int xp, int yp, int w, int h, char *p, void (*f)(MapMenu *, int), MapMenu *mm, int mID, int time = 2);
};

//OLD SHAPES

void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]);

void fillBorder(Canvas *c, Color borderColour, int width);

static void ColliderCheck(Marple * marple) {
    MapCollisionBox::colliderMapPoll(marple);
    StateCollisionBox::colliderStatePoll(marple);
    CollisionBox::colliderPoll(marple);
}