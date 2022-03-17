#include "MarpleTiltMachine.h"
#include "../graphics/MenuPages.h"

void MarpleTiltMachine::Init() {
    StartUp::GameState newState(canvas);
    currState = &newState;
    currState->OnEntry();
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