#pragma once
#include <fstream>
#include "windows.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <chrono>
#include <sstream>
#include <cstdlib>
#include <random>
using namespace std;

static struct Button_State
{
    bool is_down;
    bool changed;
};

enum
{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_ENTER,

    BUTTON_COUNT,
};

struct Input
{
    Button_State buttons[BUTTON_COUNT];
};

static bool running = true;

struct Render_State
{
    int height, width;
    void* memory;

    BITMAPINFO bitmap_info;
};

Render_State render_state;
int CellSize = 80;

vector<pair<float, string> > vecLanes;

//vecLanes
constexpr int MAP_HEIGHT = 9;
constexpr int MAP_WIDTH = 19; //real width
constexpr int MAP_WIDTH_ALLOWED = MAP_WIDTH - 3; //display width, minus 3 just like you asked
constexpr float LOWER_BOUND = -3.0f;
constexpr float UPPER_BOUND = 3.0f;

//obstacles
constexpr int MIN_DIST_OBSTACLE = 3;
constexpr int MAX_DIST_OBSTACLE = 5;
constexpr int MAX_DIST_RESPAWN_OBSTACLE_FROM_LEFT = 1;

/*
obstacles:
- 'b': bush
- 'c': cactus
- 'r': rock
*/

//horse wagons
constexpr int MIN_DIST_HORSE_WAGON = 3;
constexpr int MAX_DIST_HORSE_WAGON = 6;
constexpr int MAX_DIST_RESPAWN_HORSE_WAGON_FROM_LEFT = 1;
/*
horse wagons:
- 'h': tail
- 'H': head
*/

//logs
constexpr int MIN_DIST_LOG = 3;
constexpr int MAX_DIST_LOG = 5;
constexpr int MIN_LENGTH_LOG = 2;
constexpr int MAX_LENGTH_LOG = 4;
constexpr int MAX_DIST_RESPAWN_LOG_FROM_LEFT = 1;
/*
- 'l': log
*/

int rig(int low, int high) {
    std::mt19937 seed(std::random_device{}());
    std::uniform_int_distribution<int> dist(low, high);
    return dist(seed);
}

float rfg(float low, float high) {
    std::mt19937 seed(std::random_device{}());
    std::uniform_real_distribution<float> dist(low, high);
    return dist(seed);
}

void generateMap() {
    vecLanes.clear();
    //draw empty vecLanes
    vecLanes.resize(MAP_HEIGHT);
    for (int j = 0; j < MAP_WIDTH; ++j) {
        vecLanes[0].first = 0.0f;
        vecLanes[0].second += "=";
        vecLanes[MAP_HEIGHT - 1].first = 0.0f;
        vecLanes[MAP_HEIGHT - 1].second += "=";
    }
    for (int i = 1; i < vecLanes.size() - 1; i++) {
        int rowType = rig(0, 2); //0: pavement, 1: road, 2: river
        if (rowType == 0) {
            vecLanes[i].first = 0.0f;
            for (int j = 0; j < MAP_WIDTH; ++j) {
                vecLanes[i].second += "=";
            }
        }
        else if (rowType == 1) {
            vecLanes[i].first = rfg(LOWER_BOUND, UPPER_BOUND);
            for (int j = 0; j < MAP_WIDTH; ++j) {
                vecLanes[i].second += "-";
            }
        }
        else if (rowType == 2) {
            vecLanes[i].first = rfg(LOWER_BOUND, UPPER_BOUND);
            for (int j = 0; j < MAP_WIDTH; ++j) {
                vecLanes[i].second += "~";
            }
        }
    }

    for (int i = 0; i < MAP_HEIGHT; ++i) {
        //create obstacles
        if (vecLanes[i].second[MAP_WIDTH - 1] == '=') {
            int pos = rig(0, MAX_DIST_RESPAWN_OBSTACLE_FROM_LEFT + 1);
            while (pos < MAP_WIDTH_ALLOWED) {

                int obstacleType = rig(1, 3);
                switch (obstacleType)
                {
                case 1:
                    vecLanes[i].second[pos] = 'b';
                    break;
                case 2:
                    vecLanes[i].second[pos] = 'c';
                    break;
                case 3:
                    vecLanes[i].second[pos] = 'r';
                default:
                    break;
                }

                int dist = rig(MIN_DIST_OBSTACLE, MAX_DIST_OBSTACLE);
                pos += (dist + 1);
            }
        }
        //create horse wagons
        else if (vecLanes[i].second[MAP_WIDTH - 1] == '-') {
            int pos = rig(0, MAX_DIST_RESPAWN_HORSE_WAGON_FROM_LEFT + 1);
            while (pos < MAP_WIDTH_ALLOWED) {

                if (vecLanes[i].first < 0.0f) {
                    vecLanes[i].second[pos] = 'H';
                    vecLanes[i].second[pos + 1] = 'h';
                }
                else {
                    vecLanes[i].second[pos] = 'h';
                    vecLanes[i].second[pos + 1] = 'H';
                }

                int dist = rig(MIN_DIST_HORSE_WAGON, MAX_DIST_HORSE_WAGON);
                pos += (dist + 2);
            }
        }
        //create logs
        else {
            int pos = rig(0, MAX_DIST_RESPAWN_LOG_FROM_LEFT + 1);
            while (pos < MAP_WIDTH_ALLOWED) {

                int length = rig(MIN_LENGTH_LOG, MAX_LENGTH_LOG);
                for (int j = 0; j < length; ++j) {
                    vecLanes[i].second[pos + j] = 'l';
                }

                int dist = rig(MIN_DIST_LOG, MAX_DIST_LOG);
                pos += (dist + length + 1);
            }
        }
    }
}