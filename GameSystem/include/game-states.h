#pragma once
#include "base-state.h"
#include <ctime>

class MapLoader;
Marple* drawGameOver(rgb_matrix::Canvas *c, double elapsed);
Marple* drawTutOver(rgb_matrix::Canvas *c);

//

class GameRunning : public BaseState
{
public:
    GameRunning(rgb_matrix::Canvas *c, MapLoader *m, int ID);
    ~GameRunning();

    virtual void OnEntry() override;
    std::string Name() override;
    clock_t getTime();

protected:
    MapLoader *loader;
    int mID;
    std::clock_t startTime;
};

class GameOver : public BaseState
{
public:
    GameOver(rgb_matrix::Canvas *c, clock_t time);
    virtual void OnEntry() override;
    std::string Name() override;
protected:
    clock_t start;
};

class MoveTutorial : public BaseState
{
public:
    MoveTutorial(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class HoleTutorial : public BaseState
{
public:
    HoleTutorial(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class FullTutorial : public BaseState
{
public:
    FullTutorial(rgb_matrix::Canvas *c) : BaseState{c} {};
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
