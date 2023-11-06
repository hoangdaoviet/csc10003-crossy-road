#include "Train.h"
#include <thread>

Train::Train() : Vehicle(),
	running(false) {}

Train::Train(int x, int y, int velocity, bool isRunning) : Vehicle(x, y, velocity),
	running(isRunning) {}

bool Train::isRunning()
{
	return running;
}

void Train::setTrain(bool isRunning)
{
	this->running = isRunning;
}

void Train::countdown()
{
	std::this_thread::sleep_for(std::chrono::seconds(TRAIN_COUNTDOWN));
}


