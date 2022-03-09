#pragma once
#include "BaseState.h"

class MenuState : MarpleTilt::BaseState
{
public:
    MenuState();
    ~MenuState();

    virtual void OnEntry() = 0;
    virtual void OnExit() = 0;
    virtual void Update() = 0;
};