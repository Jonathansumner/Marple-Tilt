#pragma once
#include "game-states.h"
#include "menu-states.h"

class StartUp;
class MainMenu;

class MarpleTiltMachine {
protected:
    BaseState* prevState = nullptr;
    rgb_matrix::Canvas *canvas = nullptr;
    MPU6050* gyro = nullptr;

public:
    MarpleTiltMachine() {};
    ~MarpleTiltMachine() {};

    void Init();
    void ChangeCurrentState(BaseState *newState);
    static void StaticStateChange(MarpleTiltMachine *fsm, BaseState *nS);

    void RewindState();
    void Update();

    void Destroy();

    BaseState* GetCurrentState();

    void setCanvas(rgb_matrix::Canvas *c);
    Canvas* getCanvas();

    void setGyro(MPU6050 *g);
    MPU6050* getGyro();

    BaseState *currState = nullptr;
};