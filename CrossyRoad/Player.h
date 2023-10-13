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

	int getX();
	int getY();
	void setX(int X);
	void setY(int Y);

	void up();
	void down();
	void left();
	void right();

	bool isImpactWithCar(const Car& obj);
	bool isOnShip(const Ship& obj);
	bool isFinish();
	bool isDead();
};

#endif // !PLAYER_H
