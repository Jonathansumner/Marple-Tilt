#pragma once
#include "object.h"

class MarpleTiltMachine;
class BaseState;
class CollisionBox;
class StateCollisionBox;

class Home : public Object
{
    int diameter;

public:
    Home(float x, float y, int d);
    int getDiameter();
    float getX();
    float getY();
};

class Marple : public Object
{
private:
    int diameter;
    Home *home;

public:
    Marple(float x, float y, int d, Home *h);

    //    ~Marple();

    int getDiameter();
    void returnHome();
    static void returnWrapper(Marple *m);
    float x_velocity;
    float y_velocity;
    float x_acceleration;
    float y_acceleration;
};


class Wall : public Object
{
public:
    int diameter;
    Wall(float x, float y, int d);
};

class Hole : public Object
{
private:
    int diameter;
    CollisionBox *box;

public:
    Hole(float x, float y, int d, CollisionBox *cB);
    int getDiameter();
};

class End : public Object
{
private:
    int diameter;
    StateCollisionBox *box;

public:
    End(float x, float y, int d, void (*f)(MarpleTiltMachine *, BaseState *), MarpleTiltMachine *fsm, BaseState *ns, StateCollisionBox *sCB, int time = 1);

    int getDiameter();
};