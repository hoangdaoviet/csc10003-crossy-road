#include "Vehicle.h"
#include <thread>

Vehicle::Vehicle(): 
	x(INIT_VEHICLE_X), 
	y(INIT_VEHICLE_Y),
	velocity(0) {}

Vehicle::Vehicle(int x, int y, int velocity) :
	x(x),
	y(y),
	velocity(velocity) {}

int Vehicle::getX() const
{
	return x;
}

int Vehicle::getY() const
{
	return y;
}

int Vehicle::getVelocity() const
{
	return velocity;
}

void Vehicle::setX(int x) 
{
	this->x = x;
}

void Vehicle::setY(int y) 
{
	this->y = y;
}

void Vehicle::setVelocity(int velocity)
{
	this->velocity = velocity;
}


