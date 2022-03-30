#pragma once
#include "GameState.h" 

// StartUp State

class StartUp : public GameState
{
public:
    StartUp(Canvas *c) : GameState {c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameTerminated : GameState
{
public:
    GameTerminated(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

// Gameplay States
class GamePaused : GameState
{
public:
    GamePaused(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameRunning : GameState
{
public:
    GameRunning(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameOver : GameState
{
public:
    GameOver(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

// Tutorial States
class TutorialPaused : GameState
{
public:
    TutorialPaused(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class TutorialRunning : GameState
{
public:
    TutorialRunning(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class TutorialOver : GameState
{
public:
    TutorialOver(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};
