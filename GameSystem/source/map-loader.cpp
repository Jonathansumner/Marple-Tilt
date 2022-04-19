#include "map-loader.h"
#include "led-matrix.h"
#include "game-objects.h"
#include "collision-boxes.h"

#include <sstream>
#include <dirent.h>
#include <ios>
#include <bitset>
#include <math.h>
#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;

void MapLoader::loadFileList(bool tutorial)
{
    struct dirent *d;
    DIR *dr;

    if (tutorial)
    {
        dr = opendir("tutorial_maps");
    }
    else
    {
        dr = opendir("maps");
    }

    if (dr != NULL)
    {
        for (d=readdir(dr); d!=NULL; d=readdir(dr))
        {
            string str(d->d_name);
            if (str.find(".csv") != string::npos)
            {   
                fileList.push_back(str.substr(0, (str.length() - 4)));
            }
        }
        closedir(dr);
    }
}

vector<string> MapLoader::getFileList(int pageNum)
{
    vector<string> files;
    int len = fileList.size();

    if (len <= pageNum * 3) 
    {
        return files;
    } else if (len <= (pageNum + 1) * 3) 
    {
        return vector<string>(fileList.begin() + (pageNum * 3), fileList.end());
    } else {
        int n = pageNum * 3;
        return vector<string>(fileList.begin() + n, fileList.begin() + n + 3);
    }
}

Marple* MapLoader::loadMapFile(int fileIndex, rgb_matrix::Canvas *c, bool tutorial)
{
    ifstream file;
    int tutNum;

    if (tutorial)
    {
        file.open("tutorial_maps/" + fileList[fileIndex] + ".csv");
        tutNum = fileIndex + 1;
    }
    else
    {
        file.open("maps/" + fileList[fileIndex] + ".csv");
    }

    vector<vector<string>> mapData;
    vector<string> row;
    string line, word;

    while (getline(file, line))
    {
        row.clear();

        stringstream str(line);

        while (getline(str, word, ',')) 
        {
            row.push_back(word);
        }

        mapData.push_back(row);
    }

    file.close();

    if (mapData.size() == 0)
    {
        return nullptr;
    }

    vector<Wall*> walls;
    vector<Hole*> holes;
    int w = 0;
    int h = 0;

    Marple *m;
    bool endfound = false;

    // For every row
    for (int y=0; y<64; y++)
    {   
        // For every cell
        for (int x=0; x<64; x++)
        {
            // Is a Wall here?
            if (mapData[y][x][0] == 'W')
            {   
                // Check for 2x2 square
                if (y < 63 && x < 63 && 
                    mapData[y+1][x][0] == 'W' && 
                    mapData[y][x+1][0] == 'W' &&
                    mapData[y+1][x+1][0] == 'W') {

                    // Clear redundant data for wall piece
                    mapData[y+1][x] = "";
                    mapData[y+1][x+1] = "";

                    // Check for 3x3 square
                    if (x < 62 && y < 62 &&
                        mapData[y][x+2][0] == 'W' &&
                        mapData[y+1][x+2][0] == 'W' &&
                        mapData[y+2][x+2][0] == 'W' &&
                        mapData[y+2][x][0] == 'W' &&
                        mapData[y+2][x+1][0] == 'W')
                    {

                        // Clear redundant data for wall piece
                        mapData[y+1][x+2] = "";
                        mapData[y+2][x] = "";
                        mapData[y+2][x+1] = "";
                        mapData[y+2][x+2] = "";

                        // Add new wall of size 3x3
                        walls.push_back(new Wall(x, y, 3));
                        walls[w]->setColour(getColour(mapData[y][x].substr(2, 6)));
                        w++;

                        //cout << "Wall found at " << x << "," << y << endl; 

                        x += 2;
                    }
                    else
                    {
                        // Add new wall of size 2x2
                        walls.push_back(new Wall(x, y, 2));
                        walls[w]->setColour(getColour(mapData[y][x].substr(2, 6)));
                        w++;

                        //cout << "Wall found at " << x << "," << y << endl;

                        x++;
                    }
                }
                else
                {

                    // Add new wall of size 1x1
                    walls.push_back(new Wall(x, y, 1));
                    walls[w]->setColour(getColour(mapData[y][x].substr(2, 6)));
                    w++;

                    //cout << "Wall found at " << x << "," << y << endl;
                }
            }
            else if (mapData[y][x][0] == 'S')
            {
                int size = mapData[y][x][8] - '0';
                m = new Marple(x, y, size, new Home(x, y, size));

                if (size > 1)
                {
                    mapData[y + 1][x] = "";
                    mapData[y + 1][x + 1] = "";

                    if (size > 2)
                    {
                        mapData[y + 1][x + 2] = "";
                        mapData[y + 2][x] = "";
                        mapData[y + 2][x + 1] = "";
                        mapData[y + 2][x + 2] = "";
                        x++;
                    }
                    x++;
                }
            }
            else if (mapData[y][x][0] == 'E')
            {
                endfound = true;
                int size = mapData[y][x][8] - '0';
                drawZone(x, y, size, c, clock(), tutNum);

                if (size > 1)
                {
                    mapData[y + 1][x] = "";
                    mapData[y + 1][x + 1] = "";

                    if (size > 2)
                    {
                        mapData[y + 1][x + 2] = "";
                        mapData[y + 2][x] = "";
                        mapData[y + 2][x + 1] = "";
                        mapData[y + 2][x + 2] = "";
                        x++;
                    }
                    x++;
                }
            }
            else if (mapData[y][x][0] == 'H')
            {
                int size = mapData[y][x][8] - '0';

                holes.push_back(new Hole(x, y, size, new CollisionBox(x, y, size, size, 0, &Marple::returnWrapper, false, false)));

                if (size > 1) {
                    mapData[y + 1][x] = "";
                    mapData[y + 1][x + 1] = "";

                    if (size > 2) {
                        mapData[y + 1][x + 2] = "";
                        mapData[y + 2][x] = "";
                        mapData[y + 2][x + 1] = "";
                        mapData[y + 2][x + 2] = "";
                        x++;
                    }
                    x++;
                }
                h++;
            }
        }
    }
    mapData.clear();
    holes.clear();
    walls.clear();

    if (endfound)
    {
        return m;
    }
    else
    {
        return nullptr;
    }
}

vector<int> getColour(string hexString)
{
    int x;
    stringstream ss;
    vector<int> colours;

    for (int i=0; i<6; i+=2)
    {   
        ss.clear();
        x=0;

        ss << hex << hexString.substr(i, 2);
        ss >> x;
        colours.push_back(x);
    }

    return colours;
}