#include "Randomizer.h"

int rng(int min, int max) {
	std::mt19937 seed(std::random_device{}());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(seed);
}