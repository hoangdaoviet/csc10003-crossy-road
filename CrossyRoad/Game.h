#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Vehicle.h"
#include "Ship.h"
#include "Car.h"
#include "Utilities.h"
#include <thread>

class Game {
private:
	Player* player;
	Car* car;
public:
	Game();
	
	void setPlayerPos(int X, int Y);
	void setCarPos(int X, int Y);
	Player* getPlayer();
	Car* getCar();
	
	void exitGame(std::thread& thrd);
	~Game();
};

#endif // !GAME_H
