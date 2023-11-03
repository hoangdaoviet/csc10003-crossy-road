#include <iostream>
#include <thread>
#include <conio.h>
#include <Windows.h>

#include "Console.h"
#include "Game.h"

Game* game;
bool running = true;

void subThread() {
	game->init();
	while (running) {
		game->drawDebug();
		game->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		system("cls");
	}
}

int main() {
	game = new Game();
	std::thread t1(subThread);
	while (true) {
		int temp = toupper(_getch());
		if (temp == 27) {
			running = false;
			t1.join();
			break;
		}
	}
	game->endGame();
	delete game;
}