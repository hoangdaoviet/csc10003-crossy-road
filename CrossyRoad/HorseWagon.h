#ifndef HORSEWAGON_H
#define HORSEWAGON_H

#include "LandVehicle.h"

class HorseWagon : public LandVehicle {
public:
	HorseWagon();
	HorseWagon(int X, int Y);

	void move(int X, int Y);
	void draw();
};

#endif // !HORSEWAGON_H
