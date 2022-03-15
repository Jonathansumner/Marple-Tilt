# pragma once
# include "BaseState.h"

class GameState : MarpleTilt::BaseState {
    public:
        GameState(Canvas *c) {canvas = c;};
        ~GameState();

        virtual void OnEntry() = 0;
        virtual void OnExit() = 0;
        virtual void Update() = 0;

        Canvas *canvas = nullptr;
};