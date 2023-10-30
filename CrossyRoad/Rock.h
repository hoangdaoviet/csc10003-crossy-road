#ifndef ROCK_H
#define ROCK_H

#include "Obstacle.h"

class Rock : public Obstacle
{
public:
	Rock();
	Rock(int x, int y);

	void draw();
};

#endif // !ROCK_H
