#include "menu-states.h"
#include "map-loader.h"

#include <iostream>

void StartMenu::OnEntry()
{
    marple = drawStartMenu(canvas);
}

std::string StartMenu::Name() { return "Start Menu"; };

// Main Menu Implementations

void MainMenu::OnEntry() 
{
    marple = drawMainMenu(canvas);
}

std::string MainMenu::Name() {return stateName;};

// Settings Menu Implementations

void SettingsMenu::OnEntry()
{
    marple = drawSettingsMenu(canvas);
}

std::string SettingsMenu::Name() { return "Settings Menu"; }


// Sound Menu Implementations

void SoundMenu::OnEntry()
{
    marple = drawSoundMenu(canvas);
}

std::string SoundMenu::Name() { return "Sound Menu"; }

// Gameplay Menu Implementations

void GameplayMenu::OnEntry()
{
    marple = drawGameplayMenu(canvas);
}

std::string GameplayMenu::Name() { return "Gameplay Menu"; }

// Brightness Menu Implemenations

void BrightnessMenu::OnEntry()
{
    marple = drawBrightnessMenu(canvas);
}

std::string BrightnessMenu::Name() { return "Brightness Menu"; }

// Tutorial Menu Implementations

void TutorialMenu::OnEntry()
{
    marple = drawTutorialMenu(canvas);
}

std::string TutorialMenu::Name() { return "Tutorial Menu"; }

// Calibrate Menu Implementations

void CalibrateMenu::OnEntry()
{
    marple = drawCalibrateMenu(canvas);
}

std::string CalibrateMenu::Name() { return "Calibrate Menu"; }

// Map Menu Implemenations

MapMenu::MapMenu(rgb_matrix::Canvas *c, int p) : BaseState {c} 
{
    currPage = p;
}

MapMenu::~MapMenu()
{
    delete loader;
}

int MapMenu::getCurrPage()
{
    return currPage;
}

void MapMenu::OnEntry()
{
    loader = new MapLoader();
    loader->loadFileList();
    marple = drawMapMenu(canvas, loader->getFileList(currPage), currPage, this);
}

MapLoader* MapMenu::getLoader() 
{
    return loader; 
}

std::string MapMenu::Name() { return "Map Menu"; }
