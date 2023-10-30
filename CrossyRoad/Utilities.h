#ifndef UTILITIES_H
#define UTILITIES_H

//PLAYER
constexpr int INIT_PLAYER_X = 0;
constexpr int INIT_PLAYER_Y = 0;
constexpr int PLAYER_STEP = 1;

//VEHICLE
constexpr int INIT_VEHICLE_X = 0;
constexpr int INIT_VEHICLE_Y = 0;
constexpr int VEHICLE_STEP = 1;
constexpr int TTT_SLOW = 0; //TTT: time to travel
constexpr int TTT_NORMAL = 1;
constexpr int TTT_FAST = 2;

//OBSTACLE
constexpr int INIT_OBSTACLE_X = 0;
constexpr int INIT_OBSTACLE_Y = 0;
constexpr int OBSTACLE_MAX_PER_ROW = 10;

//GAMEPLAY
constexpr int INIT_LEVEL = 1;
constexpr int MAX_LEVEL = 100;
constexpr int MAX_LANE = 10;

//GRAPHIC
constexpr int CHAR_WIDTH = 4;
constexpr int CHAR_HEIGHT = 4;
constexpr int UNIT_WIDTH = 10;
constexpr int UNIT_HEIGHT = 10;
constexpr int MAP_WIDTH = 32;
constexpr int MAP_HEIGHT = 18;

#endif // !UTILITIES_H
