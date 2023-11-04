#ifndef WATERVEHICLE_H
#define WATERVEHICLE_H

#include "Utilities.h"

class WaterVehicle {
private:
	int x;
	int y;
public:
	WaterVehicle();
	WaterVehicle(int x, int y);

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

	void move(int timeToTravel);
	virtual void draw() = 0;
};

#endif // !WATERVEHICLE_H
