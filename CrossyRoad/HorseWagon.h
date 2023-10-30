#ifndef CAR_H
#define CAR_H

#include "LandVehicle.h"

class HorseWagon : public LandVehicle {
public:
	HorseWagon();
	HorseWagon(int X, int Y);

	void draw();
};

#endif // !CAR_H
