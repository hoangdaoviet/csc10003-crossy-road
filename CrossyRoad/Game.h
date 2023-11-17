#pragma once

#include "HorseWagon.h"
#include "Log.h"
#include "Bush.h"
#include "Cactus.h"
#include "EmptyWagon.h"
#include "Rock.h"
#include <vector>

class Game {
private:
	std::vector<std::vector<Vehicle*>> vehicles;
	std::vector<std::vector<Obstacle*>> obstacles;
public:
	Game() = default;
};