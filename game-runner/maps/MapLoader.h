#pragma once

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <dirent.h>

#include "../graphics/gfx.h"

class MapLoader
{
    std::vector<std::string> fileList;
    std::string separator;

    public:
        MapLoader() {};

        void loadFileList();
        std::vector<std::string> getFileList();

        std::vector<std::vector<std::string>> loadMapFile(std::string filename);

};