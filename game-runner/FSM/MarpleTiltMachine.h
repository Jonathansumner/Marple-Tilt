#include "GameStates.h"
#include "MenuStates.h"
#include "led-matrix.h"
#include <variant>

using namespace::rgb_matrix;

class MarpleTiltMachine {
private:
    GameState* currState;
    Canvas *canvas;

public:
    MarpleTiltMachine(Canvas *canvas);
    ~MarpleTiltMachine();

    void Init();
    void ChangeCurrentState(GameState *newState);
    void Update();

    void Destroy();

    GameState* GetCurrentState();
};