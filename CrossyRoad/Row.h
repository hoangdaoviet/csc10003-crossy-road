#ifndef ROW_H
#define ROW_H

#include "Utilities.h"
#include "Player.h"

class Row {
public:
	Row() {};

	virtual bool checkImpact(const Player& player) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
};

#endif // !ROW_H
