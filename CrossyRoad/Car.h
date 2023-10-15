#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
public:
	Car();
	Car(int X, int Y);

	void draw();
};

#endif // !CAR_H
