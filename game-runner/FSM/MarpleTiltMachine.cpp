#include "MarpleTiltMachine.h"
#include "../graphics/MenuPages.h"
#include <iostream>

void MarpleTiltMachine::Init() {
    StartUp newState(canvas);
    currState = &newState;
    currState->OnEntry();
}

void MarpleTiltMachine::ChangeCurrentState(GameState* newState) {
    currState->OnExit();

    prevState = currState;
    currState = newState;

    currState->OnEntry();
}

void MarpleTiltMachine::RewindState() {
    ChangeCurrentState(prevState);
}

void MarpleTiltMachine::Update() {
    currState->Update();
}

GameState* MarpleTiltMachine::GetCurrentState() {
    std::cout << "Current State - " << currState->Name() << std::endl;
    return currState;
}