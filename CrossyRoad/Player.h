#pragma once
#include "Map.h"
#include "Sprite.h"

class Player : public Sprite
{
private:	
	int posX;
	int posY;
	float LastTimeOnLog;
	int level;
public:
	Player();
	Player(string fileName, int x, int y);

	void SetPosition(int x, int y);
	int GetPosX();
	int GetPosY();
	void IncrementLevel();
	void SetLevel(int level);
	int GetLevel();

	float GetLastTimeOnLog();
	void SetLastTimeOnLog(float time);
	void DrawPlayer(int x0, int y0, int x1, int y1);
};