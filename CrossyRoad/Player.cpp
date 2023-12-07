#include "Player.h"

Player::Player() : 
    posX(0), 
    posY(0), 
    LastTimeOnLog(0), 
    level(1)
{
}

Player::Player(string fileName, int x, int y) : 
    Sprite(fileName), 
    posX(x), 
    posY(y), 
    LastTimeOnLog(0), 
    level(1)
{
}

void Player::SetPosition(int x, int y)
{
	posX = x;
	posY = y;
}

int Player::GetPosX()
{
	return posX;
}

int Player::GetPosY()
{
	return posY;
}

void Player::IncrementLevel()
{
    this->level++;
}

void Player::SetLevel(int level)
{
    this->level = level;
}

int Player::GetLevel()
{
    return level;
}

float Player::GetLastTimeOnLog()
{
	return this->LastTimeOnLog;
}

void Player::SetLastTimeOnLog(float time)
{
	this->LastTimeOnLog = time;
}

void Player::DrawPlayer(int x0, int y0, int x1, int y1)
{
    if (x0 >= render_state.width) return;
    if (y0 >= render_state.height) return;

    clip(x0, y0);
    clip(x1, y1);

    for (int y = y0; y < y1; y++)
    {
        unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;

        for (int x = x0; x < x1; x++)
        {
            int idx = 80 * (80 - (y - y0) - 1) + (x - x0);
            if (this->picture[idx] == 0xF2C488)
                pixel++;
            else
                *pixel++ = picture[idx];
        }
    }
}