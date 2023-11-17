#pragma once

#include "Utilities.h"
#include "HorseWagon.h"

class Player {
private:
	int x;
	int y;
	bool state; //true: alive, false: dead
	int level; //current level
public:
	Player();
	Player(int x, int y, int level = INIT_LEVEL, bool state = true);

	//getters and setters
	int getX();
	int getY();
	bool getState();
	int getLevel();
	void setX(int x);
	void setY(int y);
	void setState(bool state);
	void setLevel(int level);

	//player controls
	void up();
	void down();
	void left();
	void right();
};