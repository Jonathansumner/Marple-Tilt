#include "MarpleTiltMachine.h"
#include "../graphics/MenuPages.h"
#include <iostream>

void MarpleTiltMachine::Init() {
    currState = new StartUp(canvas);
    currState->OnEntry();
}

void MarpleTiltMachine::ChangeCurrentState(GameState* newState) {
    currState->OnExit();
    delete prevState;

    prevState = currState;
    currState = newState;

    currState->OnEntry();
}

void MarpleTiltMachine::StaticStateChange(MarpleTiltMachine* fsm, GameState * nS) {
   fsm->ChangeCurrentState(nS);
}

void MarpleTiltMachine::RewindState()
{
    ChangeCurrentState(prevState);
}

void MarpleTiltMachine::Update() {
    currState->Update();
}

GameState* MarpleTiltMachine::GetCurrentState() {
    std::cout << "Current State - " << currState->Name() << std::endl;
    return currState;
}