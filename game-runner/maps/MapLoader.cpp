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

vector<vector<string>> MapLoader::loadMap(string filename)
{
    ifstream file(filename);

    vector<vector<string>> data;
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

        data.push_back(row);
    }

    file.close();

    return data;
}

int main()
{
    MapLoader reader;

    reader.loadFileList();
    vector<vector<string>> dataList = reader.loadMap("testmap.csv");

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