#include "LandVehicle.h"
#include <thread>

LandVehicle::LandVehicle(): 
	x(INIT_VEHICLE_X), 
	y(INIT_VEHICLE_Y) {}

LandVehicle::LandVehicle(int x, int y): 
	x(x), 
	y(y) {}

int LandVehicle::getX() const
{
	return x;
}

int LandVehicle::getY() const
{
	return y;
}

void LandVehicle::setX(int x) 
{
	this->x = x;
}

void LandVehicle::setY(int y) 
{
	this->y = y;
}

void LandVehicle::move(int timeToTravel)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(timeToTravel));
	x += VEHICLE_STEP;
}


