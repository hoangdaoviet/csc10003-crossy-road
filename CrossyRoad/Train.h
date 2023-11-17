#pragma once

#include "Utilities.h"
#include "Vehicle.h"

class Train : public Vehicle {
private:
	bool running;
public:
	Train();
	Train(int x, int y, int velocity, bool isRunning = false);

	bool isRunning();
	void setTrain(bool isRunning);
	void countdown();
};