#include "Pavement.h"

Pavement::Pavement() : Row(),
	obstacles(std::vector<Obstacle*>(0)) {}

Pavement::Pavement(int number, int y) : Row(y),
	obstacles(std::vector<Obstacle*>(number, nullptr)) 
{
	int currentX = 0;
	for (int i = 0; i < number; i++) {
		int choice = rng(0, 3);
		switch (choice)
		{
		case 0:
			obstacles[i] = new Bush(currentX, y);
			break;
		case 1:
			obstacles[i] = new Cactus(currentX, y);
			break;
		case 2:
			obstacles[i] = new EmptyWagon(currentX, y);
			break;
		case 3:
			obstacles[i] = new Rock(currentX, y);
			break;
		default:
			break;
		}
		currentX += rng(1, 5);
	}
}

Pavement::~Pavement()
{
	for (int i = 0; i < obstacles.size(); i++) {
		delete obstacles[i];
	}
}

void Pavement::draw()
{
	//draw pavement before drawing obstacles
	for (int i = 0; i < obstacles.size(); ++i) {
		obstacles[i]->draw();
	}
}
