#ifndef WATERVEHICLE_H
#define WATERVEHICLE_H

#include "Utilities.h"

class WaterVehicle {
private:
	int x;
	int y;
	int velocity;
public:
	WaterVehicle();
	WaterVehicle(int x, int y, int velocity);

	int getX() const;
	int getY() const;
	int getVelocity() const;
	void setX(int x);
	void setY(int y);
	void setVelocity(int velocity);

	virtual void draw() = 0;
};

#endif // !WATERVEHICLE_H
