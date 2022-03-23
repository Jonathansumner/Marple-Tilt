# pragma once
# include "GameState.h" 

// StartUp State

class StartUp : public GameState
{
    public:
        StartUp(Canvas *c) : GameState {} {canvas = c;};
        void OnEntry() override;
        void Update() override;
};

class GameTerminated : GameState
{
    void OnEntry() override;
    void Update() override;
};

// Gameplay States
class GamePaused : GameState
{
    void OnEntry() override;
    void Update() override;
};

class GameRunning : GameState
{
    void OnEntry() override;
    void Update() override;
};

class GameOver : GameState
{
    void OnEntry() override;
    void Update() override;
};

// Tutorial States
class TutorialPaused : GameState
{
    void OnEntry() override;
    void Update() override;
};

class TutorialRunning : GameState
{
    void OnEntry() override;
    void Update() override;
};

class TutorialOver : GameState
{
    void OnEntry() override;
    void Update() override;
};
