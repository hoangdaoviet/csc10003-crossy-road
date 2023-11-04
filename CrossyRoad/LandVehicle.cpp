#include "LandVehicle.h"
#include <thread>

LandVehicle::LandVehicle(): 
	x(INIT_VEHICLE_X), 
	y(INIT_VEHICLE_Y) {}

LandVehicle::LandVehicle(int X, int Y): 
	x(X), 
	y(Y) {}

int LandVehicle::getX() const
{
	return x;
}

int LandVehicle::getY() const
{
	return y;
}

void LandVehicle::setX(int X) 
{
	this->x = X;
}

void LandVehicle::setY(int Y) 
{
	this->y = Y;
}

void LandVehicle::move(int timeToTravel)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(timeToTravel));
	x += VEHICLE_STEP;
}


