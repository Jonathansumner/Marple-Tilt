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

std::string MainMenu::Name() {return stateName;};

// Settings Menu Implementations

void SettingsMenu::OnEntry()
{
    drawSettingsMenu(canvas);
}

void SettingsMenu::Update()
{
    return;
}

std::string SettingsMenu::Name() { return "Settings Menu"; }


// Sound Menu Implementations

void SoundMenu::OnEntry()
{
    drawSoundMenu(canvas);
}

void SoundMenu::Update()
{
    return;
}

std::string SoundMenu::Name() { return "Sound Menu"; }

// Gameplay Menu Implementations

void GameplayMenu::OnEntry()
{
    drawGameplayMenu(canvas);
}

void GameplayMenu::Update()
{
    return;
}

std::string GameplayMenu::Name() { return "Gameplay Menu"; }

// Brightness Menu Implemenations

void BrightnessMenu::OnEntry()
{
    drawBrightnessMenu(canvas);
}

void BrightnessMenu::Update()
{
    return;
}

std::string BrightnessMenu::Name() { return "Brightness Menu"; }

// Tutorial Menu Implementations

void TutorialMenu::OnEntry()
{
    drawTutorialMenu(canvas);
}

void TutorialMenu::Update()
{
    return;
}

std::string TutorialMenu::Name() { return "Tutorial Menu"; }

// Calibrate Menu Implementations

void CalibrateMenu::OnEntry()
{
    drawCalibrateMenu(canvas);
}

void CalibrateMenu::Update()
{
    return;
}

std::string CalibrateMenu::Name() { return "Calibrate Menu"; }

// Map Menu Implemenations

void MapMenu::OnEntry()
{
    drawMapMenu(canvas);
}

void MapMenu::Update()
{
    return;
}

std::string MapMenu::Name() { return "Map Menu"; }
