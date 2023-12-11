#pragma once
#include "Map.h"

class Sprite
{
protected:
	vector<unsigned int> picture;

	unsigned int convertToHex(string s);
	vector<unsigned int> GetPicture(string fileName);

	void clip(int& x, int& y);
public:
	Sprite();
	Sprite(string fileName);
	void Draw1stPartSpriteAt(int x0, int y0, int x1, int y1);
	void Draw2ndPartSpriteAt(int x0, int y0, int x1, int y1);
	void DrawCredits(int x0, int y0, int x1, int y1);
};