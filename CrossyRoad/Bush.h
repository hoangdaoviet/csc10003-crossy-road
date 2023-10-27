#ifndef BUSH_H
#define BUSH_H

#include "Obstacle.h"

class Bush : public Obstacle {
public:
	Bush();
	Bush(int X, int Y);

	void draw();
};

#endif // !BUSH_H
