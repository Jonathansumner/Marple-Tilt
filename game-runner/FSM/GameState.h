# pragma once
# include "BaseState.h"

class GameState : MarpleTilt::BaseState {
    public:
        GameState(Canvas *c) {canvas = c;};
        ~GameState();

        virtual void OnEntry() = 0;
        virtual void OnExit() {canvas->Clear();};
        virtual void Update() = 0;

        Canvas *canvas = nullptr;
};