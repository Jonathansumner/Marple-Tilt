#pragma once
#include "GameState.h"
#include "../maps/MapLoader.h"

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

    void ChangePage(int change);
    static void ChangePageWrapper(MapMenu *mm, int n);

    void ChooseMap(int mapID);
    static void ChooseMapWrapper(MapMenu *mm, int mapID);

private:
    MapLoader* loader;

    int currPage = 0;
    int maxPage;
};