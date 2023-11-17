#pragma once

#include "Obstacle.h"

class Rock : public Obstacle
{
public:
	Rock();
	Rock(int x, int y);

	void draw();
};