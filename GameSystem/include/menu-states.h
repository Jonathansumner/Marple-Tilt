#pragma once
#include "base-state.h"

class MapLoader;
class Marple;
void drawMainMenu(rgb_matrix::Canvas *c);
void drawSettingsMenu(rgb_matrix::Canvas *c);
void drawSoundMenu(rgb_matrix::Canvas *c);
void drawBrightnessMenu(rgb_matrix::Canvas *c);
void drawGameplayMenu(rgb_matrix::Canvas *c);
void drawTutorialMenu(rgb_matrix::Canvas *c);
void drawCalibrateMenu(rgb_matrix::Canvas *c);
void drawZone(int x, int y, int d, Marple *m, rgb_matrix::Canvas *c, clock_t t);

// Menu States
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
    virtual void OnEntry() override;
    std::string Name() override;

    MapLoader* getLoader() {return loader;};

    int getCurrPage();

    void ChangePage(int change);
    static void ChangePageWrapper(MapMenu *mm, int n);

    void ChooseMap(int mapID);
    static void ChooseMapWrapper(MapMenu *mm, int mapID);

private:
    MapLoader* loader;

    int currPage;
    int maxPage;
};

void drawMapMenu(rgb_matrix::Canvas *c, std::vector<std::string> list, int page, MapMenu *mm);