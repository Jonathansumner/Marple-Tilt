#pragma once
#include "led-matrix.h"
#include <iostream>

using namespace rgb_matrix;

class GameState {
    public:
        GameState() {};
        virtual ~GameState();

        virtual void OnEntry();
        void OnExit() {std::cout << "Clear Canvas\n";};
        virtual void Update();

        Canvas *canvas = nullptr;
};