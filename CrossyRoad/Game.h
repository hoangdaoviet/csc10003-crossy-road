#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <vector>
#include "Console.h"
#include "Randomizer.h"
#include "Player.h"
#include "LandVehicle.h"
#include "HorseWagon.h"
#include "WaterVehicle.h"
#include "Log.h"
#include "Train.h"
#include "Utilities.h"

class Game {
<<<<<<< HEAD
private:
	Player* player;
	char** map; //actual drawing
	int** row;
	//row[i][0] = 0: pavement, 1: road, 2: river
	//row[i][1] = (< 0) : go left; (> 0) : go right 
	void movePlayer(int move = 0);
public:
	Game();
	~Game();

	void init();
	bool isPlayerAlive();
	void update(int moveDir = 0);
	void drawDebug();
	void endGame();
=======

>>>>>>> parent of ed69e5c (Major changes in gameplay implementation)
};

#endif // !GAME_H
