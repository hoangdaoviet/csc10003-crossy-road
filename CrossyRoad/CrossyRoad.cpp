#include "Game.h"

int main() {
	Console obj;
	obj.ConstructConsole(MAP_WIDTH * UNIT_WIDTH, MAP_HEIGHT * UNIT_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT);
	system("pause");
}