#include "Player.h"

Player::Player() {
	x = INIT_PLAYER_X;
	y = INIT_PLAYER_Y;
	level = INIT_LEVEL;
	state = true;
}

int Player::getX() {
	return x;
}

int Player::getY() {
	return y;
}

bool Player::getState() {
	return state;
}

void Player::setX(int X) {
	this->x = X;
}

void Player::setY(int Y) {
	this->y = Y;
}

void Player::setState(bool state_) {
	this->state = state_;
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

bool Player::isFinish() {
	return level == MAX_LEVEL;
}

bool Player::isDead() {
	return !state;
}