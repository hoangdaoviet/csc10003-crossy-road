#include "Randomizer.h"

int rng(int low, int high)
{
	std::mt19937 mersenne(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> random(low, high);
	return random(mersenne);
}