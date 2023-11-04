#include "Road.h"
#include "Randomizer.h"

Road::Road() : Row() {}

Road::Road(int number, int y) : Row(y) 
{
	for (int i = 0; i < number; i++)
	{
		landVehicles.push_back(new HorseWagon(0, y));
	}
}

Road::~Road() 
{
	for (int i = 0; i < landVehicles.size(); i++) {
		delete landVehicles[i];
	}
}

void Road::update()
{
	for (int i = 0; i < landVehicles.size(); ++i) {
		landVehicles[i]->move(TTT_SLOW);
	}
}

void Road::draw()
{
	//draw the road before drawing land vehicles
	for (int i = 0; i < landVehicles.size(); ++i) {
		landVehicles[i]->draw();
	}
}
