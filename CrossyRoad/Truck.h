#ifndef TRUCK_H
#define TRUCK_H

#include "LandVehicle.h"

class Truck : public LandVehicle {
public:
	Truck();
	Truck(int X, int Y);

	void move(int X, int Y);
	void draw();
};

#endif // !TRUCK_H
