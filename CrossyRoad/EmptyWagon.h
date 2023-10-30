#ifndef EMPTYWAGON_H
#define EMPTYWAGON_H

#include "Obstacle.h"

class EmptyWagon : public Obstacle
{
public:
	EmptyWagon();
	EmptyWagon(int x, int y);

	void draw();
};

#endif // !EMPTYWAGON_H
