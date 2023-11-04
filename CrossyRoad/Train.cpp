#include "Train.h"
#include <thread>

Train::Train(): 
	x(INIT_VEHICLE_X),
	y(INIT_VEHICLE_Y),
	running(false) {}

Train::Train(int X, int Y):
	x(X),
	y(Y),
	running(false) {}

int Train::getX() const
{
	return x;
}

int Train::getY() const
{
	return y;
}

bool Train::isRunning() const
{
	return running;
}

void Train::countDown(unsigned int time)
{
	std::this_thread::sleep_for(std::chrono::seconds(time));
	//if 5 secs remaining, red light appears
	running = true;
}

void Train::run(unsigned int time)
{
	std::this_thread::sleep_for(std::chrono::seconds(time));
	running = false;
}

void Train::draw()
{
	//draw here
}

