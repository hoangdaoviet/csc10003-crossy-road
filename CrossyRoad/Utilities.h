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

//OBJECT
constexpr int INIT_OBJECT_X = 0;
constexpr int INIT_OBJECT_Y = 0;
constexpr int OBJECT_BUSH = 0;
constexpr int OBJECT_CACTUS = 1;
constexpr int OBJECT_ROCK = 2;
constexpr int OBJECT_EMPTY_WAGON = 3;

//GAMEPLAY
constexpr int INIT_LEVEL = 1;
constexpr int MAX_LEVEL = 100;
constexpr int MAX_LANE = 10;

//GRAPHIC
/*
Guidelines:
- each character will have width of 4 pixels and height of 4 pixels
- each unit will have width of 10 characters and height of 10 characters
- the entire map will have width of 32 units and height of 18 units
- the entire screen will have size of (4x10x32)x(4x10x18) = 1280x720 pixels
- drawings will be done on a scale of characters, not pixels
- then,load the pictures into the game
*/
constexpr int CHAR_WIDTH = 4;
constexpr int CHAR_HEIGHT = 4;
constexpr int UNIT_WIDTH = 10;
constexpr int UNIT_HEIGHT = 10;
constexpr int MAP_WIDTH = 32;
constexpr int MAP_HEIGHT = 18;

#endif // !UTILITIES_H
