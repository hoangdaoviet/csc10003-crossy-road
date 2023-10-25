#ifndef CAR_H
#define CAR_H

#include "LandVehicle.h"

class Car : public LandVehicle {
public:
	Car();
	Car(int X, int Y);

	void move();
	void draw();
};

#endif // !CAR_H
