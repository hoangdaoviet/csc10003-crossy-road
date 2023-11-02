#include "Game.h"
#include <iostream>

Game::Game()
{
	player = new Player();
	map = new char* [MAP_HEIGHT];
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		map[i] = new char[MAP_WIDTH];
	}
	row = new int* [MAP_HEIGHT];
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		row[i] = new int[2];
	}
}

Game::~Game()
{
	delete player;
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		delete[] map[i];
	}
	delete[] map;
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		delete[] row[i];
	}
	delete[] row;
}

void Game::init()
{
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		if (i == 0 || i == MAP_HEIGHT - 1) row[i][0] = 0;
		else row[i][0] = rng(0, 2);

		row[i][1] = (row[i][0] == 0) ? 0 : 1 * (rng(0, 1) == 0 ? -1 : 1);

		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (row[i][0] == 0) map[i][j] = '=';
			else if (row[i][0] == 1) map[i][j] = '-';
			else map[i][j] = '~';
		}
	}

	for (int i = 0; i < MAP_HEIGHT; ++i) {
		if (row[i][0] == 1) {
			int prev = 1;
			while (prev < MAP_WIDTH) {
				int pos = rng(prev + VEHICLES_MIN_DIS, prev + VEHICLES_MAX_DIS);
				if (pos >= MAP_WIDTH || pos + 1 >= MAP_WIDTH) break;
				map[i][pos] = map[i][pos + 1] = 'h';
				prev = pos + HORSEWAGON_LENGTH;
			}
		}
		else if (row[i][0] == 2) {
			int length = rng(LOG_MIN_LENGTH, LOG_MAX_LENGTH);
			int pos = rng(0, MAP_WIDTH - length);
			for (int j = pos; j < std::min(pos + length, MAP_WIDTH); ++j) {
				map[i][j] = 'l';
			}
		}
		else {
			int prev = 0;
			while (prev < MAP_WIDTH) {
				int pos = rng(prev + OBSTACLES_MIN_DIS, prev + OBSTACLES_MAX_DIS);
				if (pos >= MAP_WIDTH) break;
				int obj = rng(0, 3);
				switch (obj)
				{
				case 0:
					map[i][pos] = 'b';
					break;
				case 1:
					map[i][pos] = 'c';
					break;
				case 2:
					map[i][pos] = 'r';
					break;
				case 3:
					if (pos + 1 >= MAP_WIDTH) break;
					else map[i][pos] = map[i][pos + 1] = 'e';
					break;
				default:
					break;
				}
				prev = pos;
			}
		}
	}
}

bool Game::isPlayerAlive()
{
	int y = player->getY();
	for (int i = 0; i < MAP_WIDTH; ++i) {
		if (row[y][0] == 1) {
			if (map[player->getX()][y] == 'h') {
				return false;
			}
		}
		else if (row[y][0] == 2) {
			if (map[player->getX()][y] != 'l') {
				return false;
			}
		}
	}
	return true;
}

void Game::update(int playerMove)
{
	for (int i = 0; i < )
}

void Game::draw()
{
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j =0; j < MAP_WIDTH; ++j) {
			std::cout << map[i][j];
		}
		std::cout << ' ' << row[i][0] << ' ' << row[i][1] << std::endl;
	}
}

void Game::endGame()
{
}
