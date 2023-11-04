#ifndef LOG_H
#define LOG_H

#include "WaterVehicle.h"

class Log : public WaterVehicle {
private:
	int length;
public:
	Log();
	Log(int x, int y, int length, int velocity);

	void draw();
};

#endif // !LOG_H
