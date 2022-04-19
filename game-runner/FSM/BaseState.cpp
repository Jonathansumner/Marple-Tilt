#include "BaseState.h"
#include "../graphics/gfx.h"

using rgb_matrix::Canvas;

BaseState::BaseState(Canvas *c)
{
    canvas = c;
}

void BaseState::OnExit()
{
    clearAll(canvas);
}

void BaseState::Update(MPU6050 *g)
{
    //updateMarple(marple, g);
    ColliderCheck(marple);
}

void BaseState::setMarple(Marple *m)
{
    marple = m;
}

Marple* BaseState::getMarple()
{
    return marple;
}