#pragma once
#include "GameState.h"
#include "../maps/MapLoader.h"

// Menu States
class MainMenu : public GameState
{
public:
    MainMenu(Canvas *c) : GameState {c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;

private:
    std::string stateName = "Main Menu";
};

class SettingsMenu : public GameState
{
public:
    SettingsMenu(Canvas *c) : GameState {c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class SoundMenu : public GameState
{
public:
    SoundMenu(Canvas *c) : GameState {c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class BrightnessMenu : public GameState
{
public:
    BrightnessMenu(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class GameplayMenu : public GameState
{
public:
    GameplayMenu(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class TutorialMenu : public GameState
{
public:
    TutorialMenu(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class CalibrateMenu : public GameState
{
public:
    CalibrateMenu(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;
};

class MapMenu : public GameState
{
public:
    MapMenu(Canvas *c) : GameState{c} {};
    void OnEntry() override;
    void Update() override;
    std::string Name() override;

private:
    MapLoader* loader;
};