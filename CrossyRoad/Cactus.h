#ifndef CACTUS_H
#define CACTUS_H

#include "Obstacle.h"

class Cactus : public Obstacle
{
public:
	Cactus();
	Cactus(int x, int y);

	void draw();
};

#endif // !CACTUS_H
