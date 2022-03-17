#include "MarpleTiltMachine.h"
#include "../graphics/MenuPages.h"

void MarpleTiltMachine::Init() {

    drawImage("img/new_logo.ppm", canvas, {0, 0, 64, 64});
}

void MarpleTiltMachine::ChangeCurrentState(GameState* newState) {
    currState->OnExit();
    delete currState;

    currState = newState;
    currState->OnEntry();
}

void MarpleTiltMachine::Update() {
    currState->Update();
}

GameState* MarpleTiltMachine::GetCurrentState() {
    return currState;
}