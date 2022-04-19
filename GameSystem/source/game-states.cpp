#include "game-states.h"
#include "map-loader.h"
#include "textbox.h"

// Game Running Function Implementations

GameRunning::GameRunning(rgb_matrix::Canvas *c, MapLoader *m, int ID) : BaseState {c}
{
    loader = m;
    mID = ID;
}

GameRunning::~GameRunning()
{
    delete loader;
}

void GameRunning::OnEntry()
{
    marple = loader->loadMapFile(mID, canvas);
    startTime = clock();
}

std::string GameRunning::Name() { return "Game Running"; }

clock_t GameRunning::getTime()
{
    return startTime;
}

// Game Over Function Implementations

GameOver::GameOver(rgb_matrix::Canvas *c, clock_t time) : BaseState {c}
{
    start = time;
}

void GameOver::OnEntry()
{
    clock_t end = clock();
    double elapsed = double(end-start) / CLOCKS_PER_SEC;

    marple = drawGameOver(canvas, elapsed);
}

std::string GameOver::Name() { return "Game Over"; }

// Tutorial Running Implementations

void MoveTutorial::OnEntry()
{
    MapLoader *loader = new MapLoader();
    loader->loadFileList(true);
    marple = loader->loadMapFile(1, canvas, true);
    Textbox *txtBox = new Textbox(2, 10, {0, 255, 50}, canvas, "Tilt to Move");
    delete loader;
}

std::string MoveTutorial::Name() { return "Tutorial - Movement"; }

void HoleTutorial::OnEntry()
{
    MapLoader *loader = new MapLoader();
    loader->loadFileList(true);
    marple = loader->loadMapFile(0, canvas, true);
    Textbox *txtBox = new Textbox(3, 10, {0, 255, 50}, canvas, "Avoid Holes");
    delete loader;
}

std::string HoleTutorial::Name() { return "Tutorial - Holes"; }

void FullTutorial::OnEntry()
{
    MapLoader *loader = new MapLoader();
    loader->loadFileList(true);
    marple = loader->loadMapFile(2, canvas, true);
    Textbox *txtBox = new Textbox(3, 10, {0, 255, 50}, canvas, "Now Play!");
    delete loader;
}

std::string FullTutorial::Name() { return "Tutorial - Full Game"; }

// Tutorial Over Implementations

void TutorialOver::OnEntry()
{
    marple = drawTutOver(canvas);
}

std::string TutorialOver::Name() { return "Tutorial Over"; }