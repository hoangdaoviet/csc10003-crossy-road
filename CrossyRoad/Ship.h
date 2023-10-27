#ifndef SHIP_H
#define SHIP_H

#include "WaterVehicle.h"

class Ship : public WaterVehicle {
public:
	Ship();
	Ship(int X, int Y);

	void move(int X, int Y);
	void draw();
};

#endif // !CAR_H
