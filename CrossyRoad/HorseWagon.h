#pragma once

#include "Vehicle.h"
#include <string>

class HorseWagon : public Vehicle {
public:
	HorseWagon();
	HorseWagon(int x, int y, int velocity);

	void draw();
	std::string getNameOfObject();
};