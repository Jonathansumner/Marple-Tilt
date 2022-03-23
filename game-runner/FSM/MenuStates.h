#pragma once
#include "GameState.h"

// Menu States
class MainMenu : public GameState
{
    public:
        MainMenu(Canvas *c) : GameState {} {canvas = c;};
        void OnEntry() override;
        void Update() override;
};

class SettingsMenu : public GameState
{
    public:
        SettingsMenu(Canvas *c) : GameState {} {canvas = c;};
        void OnEntry() override;
        void Update() override;
};

class SoundMenu : public GameState
{
    public:
        SoundMenu(Canvas *c) : GameState {} {canvas = c;};
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