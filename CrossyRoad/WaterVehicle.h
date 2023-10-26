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

	virtual void move(int X, int Y);
	virtual void draw();
};

#endif // !WATERVEHICLE_H
