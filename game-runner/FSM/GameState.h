#pragma once
#include "../graphics/gfx.h"

class MarpleTiltMachine;
class Marple;
class GameState {
    public:
        GameState(rgb_matrix::Canvas *c) {canvas = c;};
        virtual ~GameState() {};

        virtual void OnEntry() {};
        void OnExit() {clearAll(canvas); std::cout << "Clearing!\n";};
        virtual void Update() {};
        virtual std::string Name() {return "";};

        void setMarple(Marple* m) {marple=m;};
        Marple* getMarple() {return marple;};

        rgb_matrix::Canvas *canvas;
        static MarpleTiltMachine runner;
        Marple *marple = nullptr;
};  