#ifndef LANDVEHICLE_H
#define LANDVEHICLE_H

#include "Utilities.h"

class LandVehicle {
private:
	int x;
	int y;
public:
	LandVehicle();
	LandVehicle(int x, int y);

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

	void move(int timeToTravel);
	virtual void draw() = 0;
};

#endif // !VEHICLE_H
