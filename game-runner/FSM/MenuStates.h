#pragma once
#include "GameState.h"

// Menu States
class MainMenu : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class SettingsMenu : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class SoundMenu : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class BrightnessMenu : public GameState
{
    void OnEntry() override;
    void Update() override;
};

class GameplayMenu : GameState
{
    void OnEntry() override;
    void Update() override;
};

class TutorialMenu : GameState
{
    void OnEntry() override;
    void Update() override;
};

class CalibrateMenu : GameState
{
    void OnEntry() override;
    void Update() override;
};

class MapMenu : GameState
{
    void OnEntry() override;
    void Update() override;
};