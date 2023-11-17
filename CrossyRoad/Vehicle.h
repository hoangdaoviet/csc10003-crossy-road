#pragma once

#include "Utilities.h"
#include <string>

class Vehicle {
private:
	int x;
	int y;
	int velocity;
public:
	Vehicle();
	Vehicle(int x, int y, int velocity);

	int getX() const;
	int getY() const;
	int getVelocity() const;
	void setX(int x);
	void setY(int y);
	void setVelocity(int velocity);

	virtual void draw() = 0;
	virtual std::string getNameOfObject() = 0;
};