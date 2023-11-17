#pragma once

#include "Utilities.h"

class Obstacle {
private:
	int x;
	int y;
public:
	Obstacle();
	Obstacle(int x, int y);

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

	virtual void draw() = 0;
};