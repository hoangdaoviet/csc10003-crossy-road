#ifndef ROW_H
#define ROW_H

#include "Utilities.h"

class Row {
protected:
	int y;
public:
	Row() : y(0) {}
	Row(int y) : y(y) {}

	virtual void draw() = 0;
};

#endif // !ROW_H
