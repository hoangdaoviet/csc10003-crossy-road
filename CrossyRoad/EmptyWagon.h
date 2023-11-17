#pragma once

#include "Obstacle.h"

class EmptyWagon : public Obstacle
{
public:
	EmptyWagon();
	EmptyWagon(int x, int y);

	void draw();
};