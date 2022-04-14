#pragma once
#include "GameStates.h"
#include "MenuStates.h"

class MarpleTiltMachine {
private:
    GameState* prevState = nullptr;
    rgb_matrix::Canvas *canvas = nullptr;

public:
    MarpleTiltMachine() {};
    ~MarpleTiltMachine() {};

    void Init();
    void ChangeCurrentState(GameState *newState);
    static void StaticStateChange(MarpleTiltMachine *fsm, GameState *nS);

    void RewindState();
    void Update();

    void Destroy();

    GameState* GetCurrentState();
    void SetCanvas(rgb_matrix::Canvas *c) {canvas = c;};

    GameState *currState = nullptr;
};