# pragma once
# include "GameState.h"

// Menu States
class MainMenu : GameState
{
    void OnEntry();
    void Update();
};

class SettingsMenu : GameState
{
    void OnEntry();
    void Update();
};

class SoundMenu : GameState
{
    void OnEntry();
    void Update();
};

class BrightnessMenu : GameState
{
    void OnEntry();
    void Update();
};

class GameplayMenu : GameState
{
    void OnEntry();
    void Update();
};

class TutorialMenu : GameState
{
    void OnEntry();
    void Update();
};

class CalibrateMenu : GameState
{
    void OnEntry();
    void Update();
};

class MapMenu : GameState
{
    void OnEntry();
    void Update();
};