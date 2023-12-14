
#include "Sound.h"

Sound::Sound() : filePath("") {
    /*std::ifstream ci("../media/LoadGame/volume.txt");
    ci >> volumeLevel;
    ci.close();*/
    volumeLevel = 50;
    setVolume(volumeLevel);
}

Sound::~Sound() {
    /*std::ofstream co("../media/LoadGame/volume.txt");
    co << volumeLevel * 100;
    co.close();*/
}

void Sound::setVolume(double volumeLevel_) {
    if (volumeLevel_ < 0 || volumeLevel_ > 100) return;
    volumeLevel = volumeLevel_ / 100;
    DWORD newVolume = static_cast<DWORD>(volumeLevel * 0xFFFF);
    waveOutSetVolume(0, newVolume);
}

void Sound::setFilePath(std::string filePath_) {
    filePath = Path + filePath_;
}

double Sound::getVolume() {
    return volumeLevel * 100;
}

void Sound::play(std::string filePath_) {
    if (filePath == Path + filePath_) return;
    PlaySoundA(NULL, NULL, SND_PURGE);
    setFilePath(filePath_);
    DWORD newVolume = static_cast<DWORD>(volumeLevel * 0xFFFF);
    waveOutSetVolume(0, newVolume);
    PlaySoundA(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
