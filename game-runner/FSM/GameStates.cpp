#include "GameStates.h"
#include "images.h"

// StartUp Implementations
void StartUp::OnEntry()
{
    drawImage("img/new_logo.ppm", canvas, {0, 0, 64, 64});
}

void StartUp::Update()
{
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

// Game Waiting Function Implementations
void GamePaused::OnEntry() {

}

void GamePaused::Update() {
    return;
}


// Game Running Function Implementations
void GameRunning::OnEntry()
{
}

void GameRunning::Update()
{
    return;
}

// Game Over Function Implementations
void GameOver::OnEntry()
{
}

void GameOver::Update()
{
    return;
}

// Tutorial Paused Implementations

void TutorialPaused::OnEntry()
{
}

void TutorialPaused::Update()
{
    return;
}

// Tutorial Running Implementations

void TutorialRunning::OnEntry()
{
}

void TutorialRunning::Update()
{
    return;
}

// Tutorial Over Implementations

void TutorialOver::OnEntry()
{
}


void TutorialOver::Update()
{
    return;
}