#include "Obstacle.h"

Obstacle::Obstacle():
	x(0),
	y(0) {}

Obstacle::Obstacle(int X, int Y):
	x(X),
	y(Y) {}

int Obstacle::getX() const
{
	return x;
}

int Obstacle::getY() const
{
	return y;
}

void Obstacle::draw()
{
}
