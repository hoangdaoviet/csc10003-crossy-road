#ifndef SHIP_H
#define SHIP_H

#include "Vehicle.h"

class Ship : public Vehicle {
public:
	Ship();
	Ship(int X, int Y);

	void draw();
};

#endif // !CAR_H
