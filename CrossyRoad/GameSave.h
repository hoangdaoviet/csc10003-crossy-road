#pragma once
#include "Map.h"
#include "Player.h"
#include <fstream>
using namespace std;

/*
file structure:
<playerPosX><space><playerPosY><space><LEVEL>
<vecLanes::float><space><vecLanes::string>
...
*/

bool readFromSave(string filename, Player &player) {
    std::ifstream is(filename);
    if (!is) {
        return false;
    }
    int x, y, level;
    is >> x >> y >> level;
    is.get();
    player.SetPosition(x, y);
    player.SetLevel(level);

    for (int i = 0; i < MAP_HEIGHT; ++i) {
        float f;
        std::string s;
        is >> f;
        is.get();
        getline(is, s);
        vecLanes.push_back(std::make_pair(f, s));
    }
    is.close();
    return true;
}

void saveToFile(string filename, Player &player) {
    std::ofstream os(filename);
    os << player.GetPosX() << ' ' << player.GetPosY() << ' ' << player.GetLevel() << '\n';
    for (int i = 0; i < vecLanes.size(); ++i) {
        os << vecLanes[i].first << ' ' << vecLanes[i].second << '\n';
    }
}