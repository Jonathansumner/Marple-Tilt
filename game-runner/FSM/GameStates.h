#pragma once
#include "GameState.h"
#include "../graphics/images.h"

// StartUp State

class StartUp : public GameState
{
public:
    StartUp(rgb_matrix::Canvas *c) : GameState {c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameTerminated : GameState
{
public:
    GameTerminated(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

// Gameplay States
class GamePaused : GameState
{
public:
    GamePaused(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameRunning : GameState
{
public:
    GameRunning(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameOver : GameState
{
public:
    GameOver(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

// Tutorial States
class TutorialPaused : GameState
{
public:
    TutorialPaused(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class TutorialRunning : GameState
{
public:
    TutorialRunning(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class TutorialOver : GameState
{
public:
    TutorialOver(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};
