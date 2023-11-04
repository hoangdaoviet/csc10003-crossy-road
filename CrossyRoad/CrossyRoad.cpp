#include <iostream>
#include <thread>
#include <conio.h>
#include <Windows.h>

#include "Console.h"


int main() {
	Console cl;
	cl.ConstructConsole(320, 160, 4, 4);
	system("pause");
}