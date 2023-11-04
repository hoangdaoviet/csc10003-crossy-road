#include "Player.h"

Player::Player() :
	x(INIT_PLAYER_X),
	y(INIT_PLAYER_Y),
	level(INIT_LEVEL),
	state(true) {}

Player::Player(int x, int y, int level, bool state) :
	x(x),
	y(y),
	level(level),
	state(state) {}

int Player::getX() {
	return x;
}

int Player::getY() {
	return y;
}

bool Player::getState() {
	return state;
}

int Player::getLevel()
{
	return level;
}

void Player::setX(int x) {
	this->x = x;
}

void Player::setY(int y) {
	this->y = y;
}

void Player::setState(bool state) {
	this->state = state;
}

void Player::setLevel(int level)
{
	if (level >= 0 && level <= MAX_LEVEL) {
		this->level = level;
	}
}

void Player::up() {
	this->y += PLAYER_STEP;
}

void Player::down() {
	this->y -= PLAYER_STEP;
}

void Player::left() {
	this->x -= PLAYER_STEP;
}

void Player::right() {
	this->x += PLAYER_STEP;
}