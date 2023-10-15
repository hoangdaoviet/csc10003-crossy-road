#ifndef PLAYER_H
#define PLAYER_H

#include "Utilities.h"
#include "Car.h"
#include "Ship.h"

class Player {
private:
	int x;
	int y;
	bool state; //true: alive, false: dead
	int level; //current level
public:
	Player();

	//getters and setters
	int getX();
	int getY();
	bool getState();
	void setX(int X);
	void setY(int Y);
	void setState(bool state_);

	//player controls
	void up();
	void down();
	void left();
	void right();

	//check impact
	bool isFinish();
	bool isDead();
};

#endif // !PLAYER_H
