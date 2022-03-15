# pragma once
# include "GameState.h"

// Menu States
class MainMenu : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class SettingsMenu : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class SoundMenu : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class BrightnessMenu : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class GameplayMenu : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class TutorialMenu : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class CalibrateMenu : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class MapMenu : GameState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};