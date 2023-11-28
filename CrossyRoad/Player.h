#pragma once
#include "utility.h"
#include "Sprite.h"

class Player : public Sprite
{
private:	
	int posX;
	int posY;
	float LastTimeOnLog;
public:
	Player();
	Player(string fileName, int x, int y);

	void SetPosition(int x, int y);
	int GetPosX();
	int GetPosY();

	float GetLastTimeOnLog();
	void SetLastTimeOnLog(float time);
	void DrawPlayer(int x0, int y0, int x1, int y1);
};