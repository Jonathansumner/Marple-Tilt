#include "MarpleTiltMachine.h"
#include <iostream>
#include <unistd.h>

void MarpleTiltMachine::Init() {

    currState = new StartUp(canvas);
    currState->OnEntry();
    sleep(5);
    ChangeCurrentState(new MainMenu(canvas));
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
    return currState;
}