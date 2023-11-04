#include "LandVehicle.h"
#include <thread>

LandVehicle::LandVehicle(): 
	x(INIT_VEHICLE_X), 
	y(INIT_VEHICLE_Y),
	velocity(0) {}

LandVehicle::LandVehicle(int x, int y, int velocity) :
	x(x),
	y(y),
	velocity(velocity) {}

int LandVehicle::getX() const
{
	return x;
}

int LandVehicle::getY() const
{
	return y;
}

int LandVehicle::getVelocity() const
{
	return velocity;
}

void LandVehicle::setX(int x) 
{
	this->x = x;
}

void LandVehicle::setY(int y) 
{
	this->y = y;
}

void LandVehicle::setVelocity(int velocity)
{
	this->velocity = velocity;
}


