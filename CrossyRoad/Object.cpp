#include "Object.h"

Object::Object():
	x(0),
	y(0) {}

Object::Object(int X, int Y):
	x(X),
	y(Y) {}

int Object::getX() const
{
	return x;
}

int Object::getY() const
{
	return y;
}