#include "marple-tilt-machine.h"
#include <iostream>
#include <unistd.h>

using rgb_matrix::Canvas;

void MarpleTiltMachine::Init() {
    currState = new StartMenu(canvas);
    currState->OnEntry();
}

void MarpleTiltMachine::ChangeCurrentState(BaseState* newState) {
    currState->OnExit();
    currState = newState;
    currState->OnEntry();
}

void MarpleTiltMachine::StaticStateChange(MarpleTiltMachine* fsm, BaseState * nS) {
   fsm->ChangeCurrentState(nS);
}

void MarpleTiltMachine::Update() {
    currState->Update(gyro);
}

BaseState* MarpleTiltMachine::GetCurrentState() {
    return currState;
}

void MarpleTiltMachine::setCanvas(Canvas *c)
{
    canvas = c;
}

Canvas* MarpleTiltMachine::getCanvas()
{
    return canvas;
}

void MarpleTiltMachine::setGyro(MPU6050 *g)
{
    gyro = g;
}

MPU6050* MarpleTiltMachine::getGyro()
{
    return gyro;
}

MarpleTiltMachine::~MarpleTiltMachine()
{
    delete currState;
}