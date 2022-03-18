# pragma once
# include "GameState.h" 

// StartUp State

class StartUp : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class GameTerminated : public GameState
{
    void OnEntry() override;
    void Update() override;
};

// Gameplay States
class GamePaused : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class GameRunning : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class GameOver : public GameState
{
    void OnEntry() override;
    void Update() override;
};

// Tutorial States
class TutorialPaused : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class TutorialRunning : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class TutorialOver : public GameState
{
    void OnEntry() override;
    void Update() override;
};
