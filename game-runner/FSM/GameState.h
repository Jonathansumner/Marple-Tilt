# pragma once
# include "BaseState.h"

class GameState : MarpleTilt::BaseState {
    public:
        GameState();
        ~GameState();

        virtual void OnEntry() = 0;
        virtual void OnExit() = 0;
        virtual void Update() = 0;
};