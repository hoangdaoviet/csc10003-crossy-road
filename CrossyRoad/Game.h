#ifndef GAME_H
#define GAME_H

#include "Randomizer.h"
#include "Player.h"
#include "Utilities.h"

class Game {
private:
	Player* player;
	char** map; //actual drawing
	int** row;
	//row[i][0] = 0: pavement, 1: road, 2: river
	//row[i][1] = (< 0) : go left; (> 0) : go right 
	void movePlayer(int move = 0);
public:
	Game();
	~Game();

	void init();
	bool isPlayerAlive();
	void update(int moveDir = 0);
	void drawDebug();
	void endGame();
};

#endif // !GAME_H
