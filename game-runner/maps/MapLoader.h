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

#include "../graphics/gfx.h"

class MapLoader
{
    std::vector<std::string> fileList;

    public:
        MapLoader() {};
        ~MapLoader() {};

        void loadFileList();
        std::vector<std::string> getFileList();

        void loadMapFile(std::string filename);

};

std::vector<int> getColour(std::string hexString);