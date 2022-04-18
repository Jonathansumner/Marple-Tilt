#include "GameStates.h"
#include "../maps/MapLoader.h"

// StartUp Implementations
void StartUp::OnEntry()
{
    drawImage("img/new_logo.ppm", canvas, {0, 0, 64, 64});
}

std::string StartUp::Name() { return "Start Up"; }

//

void GameTerminated::OnEntry()
{
}

std::string GameTerminated::Name() { return "Game Terminated"; }

// Game Running Function Implementations

void GameRunning::OnEntry()
{
    setMarple(loader->loadMapFile(mID, canvas));
    startTime = clock();
}

std::string GameRunning::Name() { return "Game Running"; }

// Game Over Function Implementations

void GameOver::OnEntry()
{
    clock_t end = clock();
    double elapsed = double(end-start) / CLOCKS_PER_SEC;

    drawGameOver(canvas, elapsed);
}

std::string GameOver::Name() { return "Game Over"; }

// Tutorial Running Implementations

void TutorialStart::OnEntry()
{

}

std::string TutorialStart::Name() { return "Tutorial Start"; }

void MoveTutorial::OnEntry()
{
    
}

std::string MoveTutorial::Name() { return "Tutorial - Movement"; }

void HoleTutorial::OnEntry()
{
}

std::string HoleTutorial::Name() { return "Tutorial - Holes"; }

void FullTutorial::OnEntry()
{
}

std::string FullTutorial::Name() { return "Tutorial - Full Game"; }

// Tutorial Over Implementations

void TutorialOver::OnEntry()
{
}

std::string TutorialOver::Name() { return "Tutorial Over"; }