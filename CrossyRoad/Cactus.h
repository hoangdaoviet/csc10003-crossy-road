#ifndef CACTUS_H
#define CACTUS_H

#include "Obstacle.h"

class Cactus : public Obstacle
{
public:
	Cactus();
	Cactus(int X, int Y);

	void draw();
};

#endif // !CACTUS_H
