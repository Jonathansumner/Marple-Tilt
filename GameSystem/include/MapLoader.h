#pragma once

#include <string>
#include <vector>

#include "led-matrix.h"

class BaseState;
class MarpleTiltMachine;
class Wall;
class Marple;
class Home;
class Hole;
void drawZone(int x, int y, int d, rgb_matrix::Canvas *c, clock_t t, int tutNum);

class MapLoader
{
    std::vector<std::string> fileList;

    public:
        MapLoader() {};
        ~MapLoader() {};

        int loadFileList(bool tutorial = false);
        std::vector<std::string> getFileList(int n);

        Marple* loadMapFile(int fileIndex, rgb_matrix::Canvas *c, bool tutorial = false);

};

std::vector<int> getColour(std::string hexString);