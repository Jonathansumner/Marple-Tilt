# pragma once
# include "GameState.h"

// StartUp State

class StartUp: GameState {
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class GameTerminated: GameState {
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};


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


// Tutorial States
class TutorialPaused : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class TutorialRunning : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class TutorialOver : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};
