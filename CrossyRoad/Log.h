#ifndef LOG_H
#define LOG_H

#include "Vehicle.h"

class Log : public Vehicle {
private:
	int length;
public:
	Log();
	Log(int x, int y, int length, int velocity);

	void draw();
};

#endif // !LOG_H
