#include "Player.h"

Player::Player() {
	this->x = INIT_PLAYER_X;
	this->y = INIT_PLAYER_Y;
	this->level = INIT_LEVEL;
	this->state = true;
}

Player::Player(int X, int Y, int level_, bool state_) {
	this->x = X;
	this->y = Y;
	this->level = level_;
	this->state = state_;
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

bool Player::isImpact(const Car& obj) {
	if ((obj.getY() == y) && (obj.getX() == x)) return true;
	else return false;
}

bool Player::isOnShip(const Ship& obj) {
	if ((obj.getY() == y) && (obj.getX() == x)) return true;
	else return false;
}

void Player::moveWithShip(const Ship& obj) {
	x = obj.getX();
	y = obj.getY();
}

bool Player::isFinish() {
	return level == MAX_LEVEL;
}

bool Player::isDead() {
	return !state;
}