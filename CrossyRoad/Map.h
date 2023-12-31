#pragma once
#include <fstream>
#include "windows.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <chrono>
#include <sstream>
#include "RNG.h"

using namespace std;

string letters[] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"00000",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"00000",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0",

	"000000",
	"0    0",
	"    0",
	"   0",
	"  0",
	" 0",
	"000000",

	"000000",
	"     0",
	"     0",
	"000000",
	"     0",
	"     0",
	"000000",

	"    0",
	"   00",
	"  0 0",
	" 0  0",
	"000000",
	"    0",
	"    0",

	"000000",
	"0",
	"0",
	"000000",
	"     0",
	"     0",
	"000000",

	"000000",
	"0",
	"0",
	"000000",
	"0    0",
	"0    0",
	"000000",

	"000000",
	"     0",
	"     0",
	"     0",
	"     0",
	"     0",
	"     0",

	"000000",
	"0    0",
	"0    0",
	"000000",
	"0    0",
	"0    0",
	"000000",

	"000000",
	"0    0",
	"0    0",
	"000000",
	"     0",
	"     0",
	"000000",

};

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
    BUTTON_ESCAPE,
	BUTTON_BACKSPACE, 

    BUTTON_COUNT,
};

enum
{
    RED_LIGHT,
    GREEN_LIGHT
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
constexpr int MAP_WIDTH_ALLOWED = MAP_WIDTH - 3; //display width
constexpr float LOWER_BOUND = 2.0f;
constexpr float UPPER_BOUND = 3.0f;

//train
constexpr float LOWER_BOUND_TRAIN = 7.0f; //train lowest speed
constexpr float UPPER_BOUND_TRAIN = 10.0; //train highest speed
constexpr int MAX_NUMBER_RAILWAY = 1;
/*
train:
- 'p': red light
- '#': railway
*/

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

void generateMap(int level);