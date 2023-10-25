#ifndef LANDVEHICLE_H
#define LANDVEHICLE_H

#include "Utilities.h"

class LandVehicle {
private:
	int x;
	int y;
public:
	LandVehicle();
	LandVehicle(int X, int Y);

	int getX() const;
	int getY() const;
	void setX(int X);
	void setY(int Y);

	virtual void move();
	virtual void draw();
};

#endif // !VEHICLE_H
