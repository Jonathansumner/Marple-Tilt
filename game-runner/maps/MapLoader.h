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
void drawZone(int x, int y, int d, rgb_matrix::Canvas *c, clock_t t);

class MapLoader
{
    std::vector<std::string> fileList;

    public:
        MapLoader() {};
        ~MapLoader() {};

        int loadFileList();
        std::vector<std::string> getFileList(int n);

        Marple* loadMapFile(int fileIndex, rgb_matrix::Canvas *c);



};

std::vector<int> getColour(std::string hexString);