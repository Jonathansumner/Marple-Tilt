#include "MapLoader.h"

using namespace std;

void MapLoader::loadFileList()
{
    struct dirent *d;
    DIR *dr;
    dr = opendir(".");

    if (dr != NULL)
    {
        for (d=readdir(dr); d!=NULL; d=readdir(dr))
        {
            string str(d->d_name);
            if (str.find(".csv") != string::npos)
            {
                fileList.push_back(str);
            }
        }
        closedir(dr);
    }

}

vector<string> MapLoader::getFileList()
{
    return fileList;
}

vector<vector<string>> MapLoader::loadMapFile(string filename)
{
    ifstream file(filename);

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

    //
    vector<bool> currRow(64);
    vector<bool> nRow(64);
    vector<bool> n_Row(64);
    vector<bool> n__Row(64);

    // For every row
    for (int i=0; i<64; i++)
    {   
        // For every cell
        for (int j=0; j<64; j++)
        {
            // Is a Wall here?
            if (mapData[i][j] == "W" && currRow[j] != true) {

                // Check for 2x2 square
                if (j < 63 && i < 63 && 
                    mapData[i+1][j] == "W" && mapData[i][j+1] == "W" && mapData[i+1][j+1] == "W") {
                    nRow[j] = true;
                    nRow[j + 1] = true;

                    // Check for 3x3 square
                    if (j < 62 && i < 62 &&
                        mapData[i][j+2] == "W" && mapData[i+1][j+2] == "W" && 
                        mapData[i+2][j+2] == "W" && mapData[i+2][j] == "W" && 
                        mapData[i+2][j+1] == "W") {
                            
                            nRow[j+2] = true;
                            n_Row[j] = true;
                            n_Row[j+1] = true;
                            n_Row[j+2] = true;

                            // Add new wall of size 3x3
                            Wall newWall(j, i, 3);
                            newWall.setColour({25, 150, 50});

                            j+=2;
                    }
                    else
                    {
                        nRow[j] = true;
                        nRow[j+1] = true;

                        // Add new wall of size 2x2
                        Wall newWall(j, i, 2);
                        newWall.setColour({50, 100, 20});

                        j++;
                    }
                } else {
                    
                    // Add new wall of size 1x1
                    Wall newWall(j, i, 1);
                    newWall.setColour({100, 50, 200}); 
                }
            }
        }

        // Shift rows up
        currRow = nRow;
        nRow = n_Row;
        vector<bool> n_Row(64);
    }

    return mapData;
}

int main()
{
    MapLoader reader;

    reader.loadFileList();
    vector<vector<string>> dataList = reader.loadMapFile("testmap.csv");

    for (vector<string> vec : dataList)
    {
        for (string data : vec)
        {
            cout << data << ", ";
        }
        cout << endl;
    }

    for (string s : reader.getFileList())
    {
        cout << s << endl;
    }
}