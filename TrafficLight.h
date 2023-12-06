#pragma once
#include "Map.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class TrafficLight
{
private:
	vector<unsigned int> RedLight;
	vector<unsigned int> GreenLight;

	int posX, posY;
	int state;
	float fTimeSinceLastLight;

	unsigned int convertToHex(string s);
	vector<unsigned int> GetPicture(string fileName);

	void clip(int& x, int& y);
public:
	TrafficLight();
	TrafficLight(string RedLight, string GreenLight, int state, float fTimeSinceLastLight);

	void SetState(int state);
	void SetPosition(int x, int y);
	void SetfTimeSinceLastLight(float time);

	int GetPosX();
	int GetPosY();
	int GetState();
	float GetfTimeSinceLastLight();

	void DrawRedLight(int x0, int y0, int x1, int y1);
	void DrawGreenLight(int x0, int y0, int x1, int y1);

	void UpdateState(float fElapsedTime);

	void Draw(int x0, int y0, int x1, int y1);
};