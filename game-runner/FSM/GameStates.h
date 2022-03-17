# pragma once
# include "GameState.h" 

// StartUp State

class StartUp: public GameState {
    void OnEntry();
    void Update();
};

class GameTerminated: GameState {
    void OnEntry();
    void Update();
};


// Gameplay States
class GamePaused: GameState {
    void OnEntry();
    void Update();
};

class GameRunning: GameState {
    void OnEntry();
    void Update();
};

class GameOver: GameState {
    void OnEntry();
    void Update();
};


// Tutorial States
class TutorialPaused : GameState
{
    void OnEntry();
    void Update();
};

class TutorialRunning : GameState
{
    void OnEntry();
    void Update();
};

class TutorialOver : GameState
{
    void OnEntry();
    void Update();
};
