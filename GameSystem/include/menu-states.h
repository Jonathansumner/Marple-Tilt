#pragma once
#include "base-state.h"

class MapLoader;
class Marple;

Marple* drawStartMenu(rgb_matrix::Canvas *c);
Marple* drawMainMenu(rgb_matrix::Canvas *c);
Marple* drawSettingsMenu(rgb_matrix::Canvas *c);
Marple* drawSoundMenu(rgb_matrix::Canvas *c);
Marple* drawBrightnessMenu(rgb_matrix::Canvas *c);
Marple* drawGameplayMenu(rgb_matrix::Canvas *c);
Marple* drawTutorialMenu(rgb_matrix::Canvas *c);
Marple* drawCalibrateMenu(rgb_matrix::Canvas *c);

// Menu States

class StartMenu : public BaseState
{
public:
    StartMenu(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class MainMenu : public BaseState
{
public:
    MainMenu(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;

private:
    std::string stateName = "Main Menu";
};

class SettingsMenu : public BaseState
{
public:
    SettingsMenu(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class SoundMenu : public BaseState
{
public:
    SoundMenu(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class BrightnessMenu : public BaseState
{
public:
    BrightnessMenu(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class GameplayMenu : public BaseState
{
public:
    GameplayMenu(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class TutorialMenu : public BaseState
{
public:
    TutorialMenu(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class CalibrateMenu : public BaseState
{
public:
    CalibrateMenu(rgb_matrix::Canvas *c) : BaseState{c} {};
    virtual void OnEntry() override;
    std::string Name() override;
};

class MapMenu : public BaseState
{
public:
    MapMenu(rgb_matrix::Canvas *c, int p);
    ~MapMenu();

    virtual void OnEntry() override;
    std::string Name() override;

    MapLoader* getLoader();

    int getCurrPage();

private:
    MapLoader* loader;

    int currPage;
};

Marple* drawMapMenu(rgb_matrix::Canvas *c, std::vector<std::string> list, int page, MapMenu *mm);