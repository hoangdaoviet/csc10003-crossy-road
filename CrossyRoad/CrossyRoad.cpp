#include <iostream>
#include <thread>
#include <conio.h>

#include "Console.h"
#include "Game.h"

int main() {
	Game game;
	game.init();
	game.draw();
}