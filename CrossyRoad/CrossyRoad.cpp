#include <iostream>
#include <thread>
#include <conio.h>
#include <Windows.h>

#include "Console.h"
#include "Game.h"

int main() {
	int cnt = 1000;
	Game game;
	game.init();
	while (cnt--) {
		game.draw();
		game.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("cls");
	}
}