#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>

#include "Player.h"
#include "Vehicle.h"
#include "Ship.h"
#include "Car.h"
#include "Game.h"

constexpr int LEFT_LIMIT = 0;
constexpr int RIGHT_LIMIT = 10;
bool isRunning = true;

void SubThread(Car* car, Player* player) {
	int currentPos = car->getX();
	while (isRunning) {
		std::cout << "Car position: " << "(" << car->getX() << "," << car->getY() << ")" << '\n';
		std::cout << "Player position: " << "(" << player->getX() << "," << player->getY() << ")" << '\n';
		if (player->isImpact(*car)) {
			player->setState(false);
			isRunning = false;
			std::cout << "IMPACT!\n";
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
		currentPos = (car->getX() == RIGHT_LIMIT ? LEFT_LIMIT : currentPos + 1);
		car->setX(currentPos);
	}
}

int main() {
	Game* game = new Game();
	game->setPlayerPos(10, 2);
	game->setCarPos(9, 1);
	std::thread t1(SubThread, game->getCar(), game->getPlayer());
	while (true) {

		int temp = toupper(_getch());

		if (game->getPlayer()->getState() == true) {
			if (temp == 27) {
				std::cout << "Esc pressed!\n";
				isRunning = false;
				game->exitGame(t1);
				break;
			}
			else {
				std::cout << "Others pressed!\n";
			}
		}
		else {
			game->exitGame(t1);
			break;
		}
	}
	delete game;
}