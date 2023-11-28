#include "player.h"

Player::Player()
{
}

Player::Player(string fileName, int x, int y) : Sprite(fileName)
{
	posX = x;
	posY = y;
	LastTimeOnLog = 0;
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
            int idx = 80 * (y - y0) + (x - x0);
            *pixel++ = picture[idx];
        }
    }
}