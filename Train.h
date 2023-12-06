#pragma once
#include "Sprite.h"
#include "TrafficLight.h"

class Train : public Sprite
{
private:
	vector<unsigned int> SymmetricPicture;
	
	float velocity;
	int posX, posY;

	float fTimeSinceLastSpawn;
	float fTimeStop;
public:
	Train();
	Train(string fileName, int x, int y);

	void SetVelocity(float velo);
	void SetPosition(int x, int y);
	void SetfTimeStop(float time);
	void SetfTimeSinceLastSpawn(float time);

	int GetPosX();
	int GetPosY();
	float GetVelocity();
	float GetfTimeStop();
	float GetfTimeSinceLastSpawn();

	void Update(float fElapsed);
	void DrawFromLeftToRight(int x0, int y0, int x1, int y1);
	void DrawFromRightToLeft(int x0, int y0, int x1, int y1);
};

