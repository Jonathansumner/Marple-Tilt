#pragma once
#include "led-matrix.h"
#include <iostream>

using namespace rgb_matrix;

class GameState {
    public:
        GameState(rgb_matrix::Canvas *c) {canvas = c;};
        virtual ~GameState() {};

        virtual void OnEntry() {};
        void OnExit() {std::cout << "Clear Canvas\n";};
        virtual void Update() {};
        virtual std::string Name() {return "";};

        rgb_matrix::Canvas *canvas = nullptr;
};