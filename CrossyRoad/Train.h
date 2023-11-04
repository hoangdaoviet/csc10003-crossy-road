#ifndef TRAIN_H
#define TRAIN_H

#include "Utilities.h"

class Train {
private:
	int x;
	int y;
	bool running;
public:
	Train();
	Train(int x, int y);

	int getX() const;
	int getY() const;
	bool isRunning() const;

	void countDown(unsigned int time); //count down until train appear
	void run(unsigned int time); //time of train occupying the railway

	void draw(); //draw when the train is coming and running away
};

#endif // !TRAIN_H
