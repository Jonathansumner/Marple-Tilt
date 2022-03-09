# pragma once
# include "MenuState.h"

// Menu States
class MainMenu : MenuState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class SettingsMenu : MenuState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class TutorialMenu : MenuState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class CalibrateMenu : MenuState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};

class MapMenu : MenuState
{
    virtual void OnEntry() override;
    virtual void OnExit() override;
    virtual void Update() override;
};