#include "Obstacle.h"

Obstacle::Obstacle():
	x(INIT_OBSTACLE_X),
	y(INIT_OBSTACLE_Y) {}

Obstacle::Obstacle(int x, int y):
	x(x),
	y(y) {}

int Obstacle::getX() const
{
	return x;
}

int Obstacle::getY() const
{
	return y;
}

void Obstacle::setX(int x)
{
	this->x = x;
}

void Obstacle::setY(int y)
{
	this->y = y;
}


