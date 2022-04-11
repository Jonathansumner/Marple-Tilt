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

class GameState;
class MarpleTiltMachine;
class Wall;
class Marple;
class Home;
class Hole;
class MapLoader
{
    std::vector<std::string> fileList;

    public:
        MapLoader() {};
        ~MapLoader() {};

        int loadFileList();
        std::vector<std::string> getFileList();

        Marple* loadMapFile(int fileIndex);

};

std::vector<int> getColour(std::string hexString);