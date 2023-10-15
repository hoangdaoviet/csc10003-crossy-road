#ifndef VEHICLE_H
#define VEHICLE_H

#include "Utilities.h"

class Vehicle {
private:
	int x;
	int y;
public:
	Vehicle();
	Vehicle(int X, int Y);

	int getX() const;
	int getY() const;
	void setX(int X);
	void setY(int Y);

	virtual void move();
};

#endif // !VEHICLE_H
