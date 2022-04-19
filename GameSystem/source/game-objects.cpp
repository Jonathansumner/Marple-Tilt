#include "game-objects.h"

Marple::Marple(float x, float y, int d, Home *h) : Object {x, y, MARPLE}
{
    instances.push_back(this);
    diameter = d;
    x_velocity = 0;
    y_velocity = 0;
    x_acceleration = 0;
    y_acceleration = 0;
    home = h;
    red = 255;
    green = 0;
    blue = 0;
}

Marple::~Marple()
{
    delete home;
}

int Marple::getDiameter()
{
    return diameter;
}

void Marple::returnHome()
{
    setPos({home->getX(), home->getY()});
}

void Marple::returnWrapper(Marple *m)
{
    m->returnHome();
}

int Hole::getDiameter()
{
    return diameter;
}

float Home::getX()
{
    return getPos()[0];
}

float Home::getY()
{
    return getPos()[1];
}

Wall::Wall(float x, float y, int d) : Object {x, y, WALL}
{
    instances.push_back(this);
    diameter = d;
}

Home::Home(float x, float y, int d) : Object {x, y, HOME}
{
    diameter = d;
}

int Home::getDiameter()
{
    return diameter;
}

Hole::Hole(float x, float y, int d, CollisionBox *cB) : Object {x, y, HOLE}
{
    instances.push_back(this);
    diameter = d;
    box = cB;
}

End::End(float x, float y, int d, void (*f)(MarpleTiltMachine *, BaseState *), MarpleTiltMachine *fsm, BaseState *ns, StateCollisionBox *sCB, int time)
    : Object{x, y, END}
{
    green = 100;
    red = 100;
    blue = 0;
    instances.push_back(this);
    diameter = d;
    box = sCB;
}

int End::getDiameter()
{
    return diameter;
}