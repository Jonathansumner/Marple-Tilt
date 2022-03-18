#pragma once

class GameState {
    public:
        GameState(Canvas *c) {canvas = c;};
        virtual ~GameState();

        virtual void OnEntry();
        void OnExit() {canvas->Clear();};
        virtual void Update();

        Canvas *canvas = nullptr;
};