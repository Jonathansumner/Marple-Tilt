#include "menu-states.h"
#include "map-loader.h"
#include <iostream>

// Main Menu Implementations

void MainMenu::OnEntry() 
{
    drawMainMenu(canvas);
}

std::string MainMenu::Name() {return stateName;};

// Settings Menu Implementations

void SettingsMenu::OnEntry()
{
    drawSettingsMenu(canvas);
}

std::string SettingsMenu::Name() { return "Settings Menu"; }


// Sound Menu Implementations

void SoundMenu::OnEntry()
{
    drawSoundMenu(canvas);
}

std::string SoundMenu::Name() { return "Sound Menu"; }

// Gameplay Menu Implementations

void GameplayMenu::OnEntry()
{
    drawGameplayMenu(canvas);
}

std::string GameplayMenu::Name() { return "Gameplay Menu"; }

// Brightness Menu Implemenations

void BrightnessMenu::OnEntry()
{
    drawBrightnessMenu(canvas);
}

std::string BrightnessMenu::Name() { return "Brightness Menu"; }

// Tutorial Menu Implementations

void TutorialMenu::OnEntry()
{
    drawTutorialMenu(canvas);
}

std::string TutorialMenu::Name() { return "Tutorial Menu"; }

// Calibrate Menu Implementations

void CalibrateMenu::OnEntry()
{
    drawCalibrateMenu(canvas);
}

std::string CalibrateMenu::Name() { return "Calibrate Menu"; }

// Map Menu Implemenations

MapMenu::MapMenu(rgb_matrix::Canvas *c, int p) : BaseState {c} 
{
    currPage = p;
}

int MapMenu::getCurrPage()
{
    return currPage;
}

void MapMenu::OnEntry()
{
    loader = new MapLoader();
    maxPage = loader->loadFileList();

    std::cout << "Draw!\n";
    drawMapMenu(canvas, loader->getFileList(currPage), currPage, this);
}

void MapMenu::ChangePage(int change)
{
    if (change == 1)
    {
        currPage++;
        drawMapMenu(canvas, loader->getFileList(currPage), currPage, this);
    } else {
        currPage--;
        drawMapMenu(canvas, loader->getFileList(currPage), currPage, this);
    }
}

void MapMenu::ChangePageWrapper(MapMenu *mm, int n) {
    mm->ChangePage(n);
}

void MapMenu::ChooseMap(int mapID)
{
    setMarple(loader->loadMapFile(mapID, canvas));
}

void MapMenu::ChooseMapWrapper(MapMenu *mm, int mapID)
{
    mm->ChooseMap(mapID);
}

std::string MapMenu::Name() { return "Map Menu"; }
