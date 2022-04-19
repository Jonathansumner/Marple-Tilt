#pragma once
#include "game-states.h"
#include "menu-states.h"

class StartUp;
class MainMenu;

class MarpleTiltMachine {
protected:
    rgb_matrix::Canvas *canvas = nullptr;
    MPU6050* gyro = nullptr;
    BaseState *currState = nullptr;

public:
    MarpleTiltMachine() {};
    ~MarpleTiltMachine();

    void Init();
    void ChangeCurrentState(BaseState *newState);
    static void StaticStateChange(MarpleTiltMachine *fsm, BaseState *nS);

    void Update();

    BaseState* GetCurrentState();

    void setCanvas(rgb_matrix::Canvas *c);
    rgb_matrix::Canvas* getCanvas();

    void setGyro(MPU6050 *g);
    MPU6050* getGyro();
};