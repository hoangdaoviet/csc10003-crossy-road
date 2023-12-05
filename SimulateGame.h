#pragma once
#include "Map.h"
#include "Sprite.h"
#include "player.h"
#include "Train.h"
#include "TrafficLight.h"

#define is_down(b) input->buttons[b].is_down
#define	pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define	released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

using namespace std;

void clip(int& x, int& y);

void clear_screen(unsigned int color);

void draw_rectangle(int x0, int y0, int x1, int y1, unsigned int color);

void draw_player(int x0, int y0, int x1, int y1, vector<unsigned int>& player);

void FillDanger(bool* danger, int x0, int y0, int x1, int y1);

bool simulate_game(Input* input, float fTimeSinceStart, float fElapsedTime,
	Player* player, vector<Train*> &vecTrain, vector<TrafficLight*> &vecLight,
	Sprite* horse, Sprite* water, Sprite* log, Sprite* cactus, Sprite* bush, Sprite* rock, bool* danger, Sprite* reverseHorseWagon);

void RunGameLoop(HDC hdc, int dem = 1);

void RunCreditsLoop(HDC hdc, int dem = 1);