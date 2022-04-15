#pragma once
#include "BaseState.h"
#include "../graphics/images.h"
#include <ctime>

class MapLoader;
void drawGameOver(rgb_matrix::Canvas *c, double elapsed);

// StartUp State

class StartUp : public BaseState
{
public:
    StartUp(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class GameTerminated : public BaseState
{
public:
    GameTerminated(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

// Gameplay States
class GamePaused : public BaseState
{
public:
    GamePaused(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class GameRunning : public BaseState
{
public:
    GameRunning(rgb_matrix::Canvas *c, MapLoader *m, int ID) : BaseState{c} {loader = m; mID = ID;};
    virtual void OnEntry() override;
    std::string Name() override;
    clock_t getTime() {return startTime;};

protected:
    MapLoader *loader;
    int mID;
    std::clock_t startTime;
};

class GameOver : public BaseState
{
public:
    GameOver(rgb_matrix::Canvas *c, clock_t time) : BaseState{c} {start = time;};
    virtual void OnEntry() override;
    std::string Name() override;
protected:
    clock_t start;
};

// Tutorial States
class TutorialPaused : public BaseState
{
public:
    TutorialPaused(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class TutorialRunning : public BaseState
{
public:
    TutorialRunning(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class TutorialOver : public BaseState
{
public:
    TutorialOver(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};
