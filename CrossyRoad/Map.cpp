#include "Map.h"

//bool running = false;


void generateMap(int level) {
    vecLanes.clear();
    //draw empty vecLanes
    vecLanes.resize(MAP_HEIGHT);
    int railwayNum = MAX_NUMBER_RAILWAY;
    for (int j = 0; j < MAP_WIDTH; ++j) {
        vecLanes[0].first = 0.0f;
        vecLanes[0].second += "=";
        vecLanes[MAP_HEIGHT - 1].first = 0.0f;
        vecLanes[MAP_HEIGHT - 1].second += "=";
    }
    for (int i = 1; i < vecLanes.size() - 1; i++) {
        int rowType = rig(0, (railwayNum > 0 ? 3 : 2)); //0: pavement, 1: road, 2: river, 3: railway
        int type = rig(0, 1);

        if (rowType == 0) {
            vecLanes[i].first = 0.0f;
            for (int j = 0; j < MAP_WIDTH; ++j) {
                vecLanes[i].second += "=";
            }
        }
        else if (rowType == 1) {
            if (type == 0)
                vecLanes[i].first = rfg(LOWER_BOUND + level, UPPER_BOUND + level);
            else if (type == 1)
                vecLanes[i].first = rfg(-UPPER_BOUND - level, -LOWER_BOUND - level);

            for (int j = 0; j < MAP_WIDTH; ++j) {
                vecLanes[i].second += "-";
            }
        }
        else if (rowType == 2) {
            if (type == 0)
                vecLanes[i].first = rfg(LOWER_BOUND + level, UPPER_BOUND + level);
            else if (type == 1)
                vecLanes[i].first = rfg(-UPPER_BOUND - level, -LOWER_BOUND - level);

            for (int j = 0; j < MAP_WIDTH; ++j) {
                vecLanes[i].second += "~";
            }
        }
        else if (rowType == 3) {
            if (type == 0)
                vecLanes[i].first = rfg(LOWER_BOUND_TRAIN + level, UPPER_BOUND_TRAIN + level);
            else if (type == 1)
                vecLanes[i].first = rfg(-UPPER_BOUND_TRAIN - level, -LOWER_BOUND_TRAIN - level);

            railwayNum--;
            for (int j = 0; j < MAP_WIDTH; ++j) {
                vecLanes[i].second += '#';//train
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
            int num = 0;
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
        else if (vecLanes[i].second[MAP_WIDTH - 1] == '~') {
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
        else if (vecLanes[i].second[MAP_WIDTH - 1] == '#') {
            if (vecLanes[i].first > 0.0f) {
                int lightPos = rig(10, 12);
                vecLanes[i].second[lightPos] = 'p'; //traffic light on railway
            }
            else {
                int lightPos = rig(2, 4);
                vecLanes[i].second[lightPos] = 'p'; //traffic light on railway
            }
        }
    }
}