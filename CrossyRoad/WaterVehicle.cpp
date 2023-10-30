#include "WaterVehicle.h"
#include <thread>

WaterVehicle::WaterVehicle() :
	x(INIT_VEHICLE_X),
	y(INIT_VEHICLE_Y) {}

WaterVehicle::WaterVehicle(int X, int Y) :
	x(X),
	y(Y) {}

int WaterVehicle::getX() const
{
	return x;
}

int WaterVehicle::getY() const
{
	return y;
}

void WaterVehicle::setX(int X)
{
	this->x = X;
}

void WaterVehicle::setY(int Y)
{
	this->y = Y;
}

void WaterVehicle::move(int timeToTravel)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(timeToTravel));
	x += VEHICLE_STEP;
}
