#include "Game.h"

Game::Game()
{
	player = new Player(0,0);
	car = new Car();
}

void Game::setPlayerPos(int X, int Y)
{
	player->setX(X);
	player->setY(Y);
}

void Game::setCarPos(int X, int Y)
{
	car->setX(X);
	car->setY(Y);
}

void Game::exitGame(std::thread& thrd)
{
	thrd.join();
}

Player* Game::getPlayer()
{
	return player;
}

Car* Game::getCar()
{
	return car;
}

Game::~Game()
{
	delete car; car = nullptr;
	delete player; player = nullptr;
}


