#pragma once
#include "GameState.h"

class MapLoader;
class Marple;
void drawMainMenu(rgb_matrix::Canvas *c);
void drawSettingsMenu(rgb_matrix::Canvas *c);
void drawSoundMenu(rgb_matrix::Canvas *c);
void drawBrightnessMenu(rgb_matrix::Canvas *c);
void drawGameplayMenu(rgb_matrix::Canvas *c);
void drawTutorialMenu(rgb_matrix::Canvas *c);
void drawCalibrateMenu(rgb_matrix::Canvas *c);
void drawMapMenu(rgb_matrix::Canvas *c, std::vector<std::string> list, int page, MapMenu *mm);

// Menu States
class MainMenu : public GameState
{
public:
    MainMenu(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;

private:
    std::string stateName = "Main Menu";
};

class SettingsMenu : public GameState
{
public:
    SettingsMenu(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class SoundMenu : public GameState
{
public:
    SoundMenu(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class BrightnessMenu : public GameState
{
public:
    BrightnessMenu(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameplayMenu : public GameState
{
public:
    GameplayMenu(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class TutorialMenu : public GameState
{
public:
    TutorialMenu(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class CalibrateMenu : public GameState
{
public:
    CalibrateMenu(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class MapMenu : public GameState
{
public:
    MapMenu(rgb_matrix::Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;

    MapLoader* getLoader() {return loader;};

    void ChangePage(int change);
    static void ChangePageWrapper(MapMenu *mm, int n);

    void ChooseMap(int mapID);
    static void ChooseMapWrapper(MapMenu *mm, int mapID);

private:
    MapLoader* loader;

    int currPage = 0;
    int maxPage;
};