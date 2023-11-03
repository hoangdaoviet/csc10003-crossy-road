#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() 
{
    ifstream file("image.txt");
    if (!file) 
    {
        cout << "Can't open image";
        return 1;
    }

    vector<vector<string>> imageColors;
    string line;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        vector<string> rowColors;
        string color;

        while (iss >> color) 
        {
            rowColors.push_back(color);
        }

        imageColors.push_back(rowColors);
    }

    for (const auto &rowColors : imageColors) {
        for (const string &color : rowColors) {
            cout << "\033[48;2;" << stoul(color.substr(1, 2), 0, 16) << ";"
                      << stoul(color.substr(3, 2), 0, 16) << ";"
                      << stoul(color.substr(5, 2), 0, 16) << "m";
            cout << " ";
        }

        cout << "\033[0m" << endl;
    }

    return 0;
}
