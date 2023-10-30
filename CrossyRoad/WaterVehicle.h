#ifndef WATERVEHICLE_H
#define WATERVEHICLE_H

#include "Utilities.h"

class WaterVehicle {
private:
	int x;
	int y;
public:
	WaterVehicle();
	WaterVehicle(int X, int Y);

	int getX() const;
	int getY() const;
	void setX(int X);
	void setY(int Y);

	void move(int timeToTravel);
	virtual void draw() = 0;
};

#endif // !WATERVEHICLE_H
