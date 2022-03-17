#include "MenuStates.h"
#include "../graphics/MenuPages.h"

// Main Menu Implementations

void MainMenu::OnEntry() {
    char *argv[4];
    drawMainMenu(canvas);
}

void MainMenu::OnExit() {
    canvas->Clear();
}

void MainMenu::Update() {

}


// Settings Menu Implementations

void SettingsMenu::OnEntry() {
    char *argv[4];
    drawSettingsMenu(canvas);
}

void SettingsMenu::OnExit()
{
    canvas->Clear();
}

void SettingsMenu::Update()
{
}


// Sound Menu Implementations

void SoundMenu::OnEntry()
{
}

void SoundMenu::OnExit()
{
}

void SoundMenu::Update()
{
}


// Gameplay Menu Implementations

void GameplayMenu::OnEntry()
{
}

void GameplayMenu::OnExit()
{
}

void GameplayMenu::Update()
{
}

// Brightness Menu Implemenations

void BrightnessMenu::OnEntry()
{
}

void BrightnessMenu::OnExit()
{
}

void BrightnessMenu::Update()
{
}

// Tutorial Menu Implementations

void TutorialMenu::OnEntry()
{
}

void TutorialMenu::OnExit()
{
}

void TutorialMenu::Update()
{
}

// Calibrate Menu Implementations

void CalibrateMenu::OnEntry()
{
}

void CalibrateMenu::OnExit()
{
}

void CalibrateMenu::Update()
{
}

// Map Menu Implemenations

void MapMenu::OnEntry()
{
}

void MapMenu::OnExit()
{
}

void MapMenu::Update()
{
}