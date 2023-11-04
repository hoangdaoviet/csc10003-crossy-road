#include "WaterVehicle.h"
#include <thread>

WaterVehicle::WaterVehicle() :
	x(INIT_VEHICLE_X),
	y(INIT_VEHICLE_Y),
	velocity(0) {}

WaterVehicle::WaterVehicle(int x, int y, int velocity) :
	x(x),
	y(y),
	velocity(velocity) {}

int WaterVehicle::getX() const
{
	return x;
}

int WaterVehicle::getY() const
{
	return y;
}

int WaterVehicle::getVelocity() const
{
	return velocity;
}

void WaterVehicle::setX(int x)
{
	this->x = x;
}

void WaterVehicle::setY(int y)
{
	this->y = y;
}

void WaterVehicle::setVelocity(int velocity)
{
	this->velocity = velocity;
}
