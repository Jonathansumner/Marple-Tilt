# pragma once

class GameState {
    public:
        GameState(Canvas *c) {canvas = c;};
        ~GameState();

        virtual void OnEntry();
        virtual void OnExit() {canvas->Clear();};
        virtual void Update();

        Canvas *canvas = nullptr;
};