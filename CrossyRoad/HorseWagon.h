#ifndef CAR_H
#define CAR_H

#include "LandVehicle.h"

class HorseWagon : public LandVehicle {
public:
	HorseWagon();
	HorseWagon(int x, int y);

	void draw();
};

#endif // !CAR_H
