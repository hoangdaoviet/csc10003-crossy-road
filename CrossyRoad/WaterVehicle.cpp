#include "WaterVehicle.h"

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

void WaterVehicle::move(int X, int Y)
{
	this->x = X;
	this->y = Y;
}

void WaterVehicle::draw()
{
}
