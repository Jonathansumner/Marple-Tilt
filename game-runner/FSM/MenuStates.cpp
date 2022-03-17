#include "MenuStates.h"
#include "../graphics/MenuPages.h"

// Main Menu Implementations

void MainMenu::OnEntry() 
{
    drawMainMenu(canvas);
}

void MainMenu::Update() 
{
    return;
}


// Settings Menu Implementations

void SettingsMenu::OnEntry()
{
    drawSettingsMenu(canvas);
}

void SettingsMenu::Update()
{
    return;
}


// Sound Menu Implementations

void SoundMenu::OnEntry()
{
    drawSoundMenu(canvas);
}

void SoundMenu::Update()
{
    return;
}


// Gameplay Menu Implementations

void GameplayMenu::OnEntry()
{
    drawGameplayMenu(canvas);
}

void GameplayMenu::Update()
{
    return;
}

// Brightness Menu Implemenations

void BrightnessMenu::OnEntry()
{
    drawBrightnessMenu(canvas);
}

void BrightnessMenu::Update()
{
    return;
}

// Tutorial Menu Implementations

void TutorialMenu::OnEntry()
{
    drawTutorialMenu(canvas);
}

void TutorialMenu::Update()
{
    return;
}

// Calibrate Menu Implementations

void CalibrateMenu::OnEntry()
{
    drawCalibrateMenu(canvas);
}

void CalibrateMenu::Update()
{
    return;
}

// Map Menu Implemenations

void MapMenu::OnEntry()
{
    drawMapMenu(canvas);
}

void MapMenu::Update()
{
    return;
}