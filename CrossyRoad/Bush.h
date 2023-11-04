#ifndef BUSH_H
#define BUSH_H

#include "Obstacle.h"

class Bush : public Obstacle
{
public:
	Bush();
	Bush(int x, int y);

	void draw();
};

#endif // !BUSH_H
