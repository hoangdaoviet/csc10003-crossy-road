#include "Vehicle.h"

Vehicle::Vehicle(): 
	x(INIT_VEHICLE_X), 
	y(INIT_VEHICLE_Y) {}

Vehicle::Vehicle(int X, int Y): 
	x(X), 
	y(Y) {}

int Vehicle::getX() const{
	return x;
}

int Vehicle::getY() const{
	return y;
}

void Vehicle::setX(int X) {
	this->x = X;
}

void Vehicle::setY(int Y) {
	this->y = Y;
}

void Vehicle::move() {
	this->x += VEHICLE_STEP;
}