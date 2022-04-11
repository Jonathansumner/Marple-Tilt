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
class MapLoader
{
    std::vector<std::string> fileList;

    public:
        MapLoader() {};
        ~MapLoader() {};

        int loadFileList();
        std::vector<std::string> getFileList();

        void loadMapFile(int fileIndex);

};

std::vector<int> getColour(std::string hexString);