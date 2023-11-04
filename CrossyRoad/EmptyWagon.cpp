#include "EmptyWagon.h"

EmptyWagon::EmptyWagon() : Obstacle() {}

EmptyWagon::EmptyWagon(int x, int y) : Obstacle(x, y) {}

void EmptyWagon::draw()
{
	//draw empty wagon here
}