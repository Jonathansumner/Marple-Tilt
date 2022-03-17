#include "MarpleTiltMachine.h"
#include "../graphics/sequences.h"

void MarpleTiltMachine::Init() {

    char *argv[4];
    int dims[4] = {0, 0, 64, 64};
    drawImage("img/new_logo.ppm", argv, canvas, dims);
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