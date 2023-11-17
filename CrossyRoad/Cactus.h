#pragma once

#include "Obstacle.h"

class Cactus : public Obstacle
{
public:
	Cactus();
	Cactus(int x, int y);

	void draw();
};