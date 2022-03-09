# pragma once
# include "GameState.h"

// Gameplay States
class GamePaused: GameState {
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class GameRunning: GameState {
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class GameOver: GameState {
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};