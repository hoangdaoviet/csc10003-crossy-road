#include "Obstacle.h"

Obstacle::Obstacle():
	x(0),
	y(0),
	code(-1) {}

Obstacle::Obstacle(int X, int Y, int code):
	x(X),
	y(Y),
	code(code) {}

int Obstacle::getX() const
{
	return x;
}

int Obstacle::getY() const
{
	return y;
}