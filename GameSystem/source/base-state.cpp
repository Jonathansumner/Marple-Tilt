#include "base-state.h"
#include "render.h"
#include "dynamics.h"

using rgb_matrix::Canvas;

BaseState::BaseState(Canvas *c)
{
    canvas = c;
}

void BaseState::OnExit()
{
    clearAll(canvas);
}

void BaseState::Update(MPU6050 *g, volatile float x, volatile float y, volatile float z)
{
    updateMarple(marple, g, x, y, z);
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