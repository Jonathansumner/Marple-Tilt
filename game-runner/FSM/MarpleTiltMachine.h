#include "GameStates.h"
#include "MenuStates.h"
#include "led-matrix.h"

class MarpleTiltMachine {
private:
    GameState* currState = nullptr;
    GameState* prevState = nullptr;
    Canvas *canvas = nullptr;

public:
    MarpleTiltMachine(Canvas *c) {canvas = c;};
    ~MarpleTiltMachine() {};

    void Init();
    void ChangeCurrentState(GameState *newState);
    void RewindState();
    void Update();

    void Destroy();

    GameState* GetCurrentState();
};