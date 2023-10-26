#ifndef LOG_H
#define LOG_H

#include "WaterVehicle.h"

class Log : public WaterVehicle {
public:
	Log();
	Log(int X, int Y);

	void move(int X, int Y);
	void draw();
};

#endif // !LOG_H
