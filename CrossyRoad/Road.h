#ifndef ROAD_H
#define ROAD_H

#include "HorseWagon.h"
#include "Row.h"
#include <vector>

class Road : public Row {
private:
	std::vector<LandVehicle*> landVehicles;
public:
	Road();
	Road(int number, int y);
	~Road();

	void update();
	void draw();
};

#endif // !ROAD_H
