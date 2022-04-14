#pragma once
#include "GameState.h"
#include "../graphics/images.h"
#include <ctime>

class MapLoader;
void drawGameOver(rgb_matrix::Canvas *c, double elapsed);

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
    clock_t getTime() {return startTime;};

protected:
    MapLoader *loader;
    int mID;
    std::clock_t startTime;
};

class GameOver : public GameState
{
public:
    GameOver(rgb_matrix::Canvas *c, clock_t time) : GameState{c} {start = time;};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
protected:
    clock_t start;
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
