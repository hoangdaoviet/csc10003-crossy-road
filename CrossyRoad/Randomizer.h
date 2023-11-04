#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>
#include <ctime>
#include <cstdlib>

template <typename T>
T rng(T low, T high)
{
	std::mt19937 mersenne(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<T> random(low, high);
	return random(mersenne);
}

#endif // !RANDOMIZER_H
