#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class HorseWagon : public Vehicle {
public:
	HorseWagon();
	HorseWagon(int x, int y, int velocity);

	void draw();
};

#endif // !CAR_H
