#pragma once

#include "Vehicle.h"
#include <string>

class Log : public Vehicle {
private:
	int length;
public:
	Log();
	Log(int x, int y, int length, int velocity);

	void draw();
	std::string getNameOfObject();
};