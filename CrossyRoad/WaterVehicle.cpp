#include "WaterVehicle.h"
#include <thread>

WaterVehicle::WaterVehicle() :
	x(INIT_VEHICLE_X),
	y(INIT_VEHICLE_Y) {}

WaterVehicle::WaterVehicle(int x, int y) :
	x(x),
	y(y) {}

int WaterVehicle::getX() const
{
	return x;
}

int WaterVehicle::getY() const
{
	return y;
}

void WaterVehicle::setX(int x)
{
	this->x = x;
}

void WaterVehicle::setY(int y)
{
	this->y = y;
}

void WaterVehicle::move(int timeToTravel)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(timeToTravel));
	x += VEHICLE_STEP;
}
