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
	Player(int X, int Y, int level_ = INIT_LEVEL, bool state_ = true);

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
	bool isImpact(const Car& obj);
	bool isOnShip(const Ship& obj);
	void moveWithShip(const Ship& obj);
	bool isFinish();
	bool isDead();
};

#endif // !PLAYER_H
