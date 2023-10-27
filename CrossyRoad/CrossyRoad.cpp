#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <vector>

#include "Console.h"
#include "Game.h"
#include "LandVehicle.h"
#include "HorseWagon.h"

int main() {
	Console obj;
	obj.ConstructConsole(MAP_WIDTH * UNIT_WIDTH, MAP_HEIGHT * UNIT_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT);
	system("pause");
}