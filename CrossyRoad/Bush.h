#pragma once

#include "Obstacle.h"

class Bush : public Obstacle
{
public:
	Bush();
	Bush(int x, int y);

	void draw();
};