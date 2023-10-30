#ifndef PAVEMENT_H
#define PAVEMENT_H

#include "Row.h"
#include "Bush.h"
#include "Cactus.h"
#include "EmptyWagon.h"
#include "Rock.h"
#include "Randomizer.h"
#include <vector>

class Pavement : public Row
{
private:
	std::vector<Obstacle*> obstacles;
public:
	Pavement();
	Pavement(int number, int y);
	~Pavement();

	void draw();
};

#endif // !PAVEMENT_H
