#pragma once
#include "GameStates.h"
#include "MenuStates.h"
#include "led-matrix.h"

class MarpleTiltMachine {
private:
    GameState* currState = nullptr;
    GameState* prevState = nullptr;
    rgb_matrix::Canvas *canvas = nullptr;

public:
    MarpleTiltMachine(rgb_matrix::Canvas *c) {canvas = c;};
    ~MarpleTiltMachine() {};

    void Init();
    void ChangeCurrentState(GameState *newState);
    static void StaticStateChange(MarpleTiltMachine *fsm, GameState *nS);

    void RewindState();
    void Update();

    void Destroy();

    GameState* GetCurrentState();
};