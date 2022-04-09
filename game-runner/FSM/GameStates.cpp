#include "GameStates.h"

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
}

void GameRunning::Update()
{
    return;
}

std::string GameRunning::Name() { return "Game Running"; }

// Game Over Function Implementations
void GameOver::OnEntry()
{
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