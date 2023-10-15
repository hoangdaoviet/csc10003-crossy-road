#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Player.h"
#include "Vehicle.h"
#include "Ship.h"
#include "Car.h"

bool running = true;

void printPlayerPos(Player* player) {
	std::cout << "Current position: " << player->getX() << ' ' << player->getY() << '\n';
}

int main() {
	Player* player = new Player();
	while (running) {
		printPlayerPos(player);
		int temp = toupper(_getch());
		
		if (temp == 87) player->up();
		if (temp == 83) player->down();
		if (temp == 65) player->left();
		if (temp == 68) player->right();

		if (temp == 27) running = false;
	}
	delete player;
	player = nullptr;
}