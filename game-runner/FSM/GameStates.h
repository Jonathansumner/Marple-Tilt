#pragma once
#include "GameState.h"
#include "../graphics/images.h"

class MapLoader;
// StartUp State

class StartUp : public GameState
{
public:
    StartUp(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    void OnExit();
    std::string Name() override;
};

class GameTerminated : public GameState
{
public:
    GameTerminated(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

// Gameplay States
class GamePaused : public GameState
{
public:
    GamePaused(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameRunning : public GameState
{
public:
    GameRunning(rgb_matrix::Canvas *c, MapLoader *m, int ID) : GameState{c} {loader = m; mID = ID;};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
protected:
    MapLoader *loader;
    int mID;

};

class GameOver : public GameState
{
public:
    GameOver(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

// Tutorial States
class TutorialPaused : public GameState
{
public:
    TutorialPaused(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class TutorialRunning : public GameState
{
public:
    TutorialRunning(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class TutorialOver : public GameState
{
public:
    TutorialOver(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};
