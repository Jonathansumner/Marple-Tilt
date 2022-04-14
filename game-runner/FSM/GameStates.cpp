#include "GameStates.h"
#include "../maps/MapLoader.h"

// StartUp Implementations
void StartUp::OnEntry()
{
    drawImage("img/new_logo.ppm", canvas, {0, 0, 64, 64});
}

void StartUp::Update()
{
    return;
}

std::string StartUp::Name() { return "Start Up"; }

void StartUp::OnExit() {
    return;
}

// Game Terminated Implementations
void GameTerminated::OnEntry()
{
}

void GameTerminated::Update()
{
    return;
}

std::string GameTerminated::Name() { return "Game Terminated"; }

// Game Waiting Function Implementations
void GamePaused::OnEntry() {

}

void GamePaused::Update() {
    return;
}

std::string GamePaused::Name() { return "Game Paused"; }

// Game Running Function Implementations
void GameRunning::OnEntry()
{
    setMarple(loader->loadMapFile(mID, canvas));
    startTime = clock();
}

void GameRunning::Update()
{
    return;
}

std::string GameRunning::Name() { return "Game Running"; }

// Game Over Function Implementations
void GameOver::OnEntry()
{
    clock_t end = clock();
    double elapsed = double(end-start) / CLOCKS_PER_SEC;

    drawGameOver(canvas, elapsed);
}

void GameOver::Update()
{
    return;
}

std::string GameOver::Name() { return "Game Over"; }

// Tutorial Paused Implementations

void TutorialPaused::OnEntry()
{
}

void TutorialPaused::Update()
{
    return;
}

std::string TutorialPaused::Name() { return "Tutorial Paused"; }

// Tutorial Running Implementations

void TutorialRunning::OnEntry()
{
}

void TutorialRunning::Update()
{
    return;
}

std::string TutorialRunning::Name() { return "Tutorial Running"; }

// Tutorial Over Implementations

void TutorialOver::OnEntry()
{
}


void TutorialOver::Update()
{
    return;
}

std::string TutorialOver::Name() { return "Tutorial Over"; }