#pragma once 

#include "Windows.h"
#include <iostream>
#include <fstream>

class Sound {
public:
    Sound();
    ~Sound();
    void play(std::string filePath);
    void setVolume(double volumeLevel);
    double getVolume();
private:
    const std::string Path = "../media/music/";
    void setFilePath(std::string filePath);
    double volumeLevel;
    std::string filePath;
};