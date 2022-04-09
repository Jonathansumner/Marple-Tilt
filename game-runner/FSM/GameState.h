#pragma once
#include "led-matrix.h"

class MarpleTiltMachine;
class GameState {
    public:
        GameState(rgb_matrix::Canvas *c) {canvas = c;};
        virtual ~GameState() {};

        virtual void OnEntry() {};
        void OnExit() {};
        virtual void Update() {};
        virtual std::string Name() {return "";};

        rgb_matrix::Canvas *canvas = nullptr;
        static MarpleTiltMachine runner;
};  