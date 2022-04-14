#pragma once

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <dirent.h>
#include <ios>
#include <bitset>
#include <math.h>
#include "led-matrix.h"

class GameState;
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
        std::vector<std::string> getFileList();

        Marple* loadMapFile(int fileIndex, rgb_matrix::Canvas *c);

};

std::vector<int> getColour(std::string hexString);