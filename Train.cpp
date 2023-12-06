#include "Train.h"

Train::Train() : Sprite()
{

}

Train::Train(string fileName, int x, int y) : Sprite(fileName)
{
    this->posX = x;
    this->posY = y;
    this->fTimeSinceLastSpawn = 0;

    for (int y = 0; y < 80; y++)
    {
        for (int x = 719; x >= 0; x--)
        {
            this->SymmetricPicture.push_back(this->picture[y * 720 + x]);
        }
    }
}

int Train::GetPosX()
{
    return this->posX;
}

int Train::GetPosY()
{
    return this->posY;
}

float Train::GetVelocity()
{
    return this->velocity;
}

float Train::GetfTimeStop()
{
    return this->fTimeStop;
}

float Train::GetfTimeSinceLastSpawn()
{
    return this->fTimeSinceLastSpawn;
}

void Train::SetPosition(int x, int y)
{
    this->posX = x;
    this->posY = y;
}

void Train::SetVelocity(float velo)
{
    this->velocity = velo;
}

void Train::SetfTimeStop(float time)
{
    this->fTimeStop = time;
}

void Train::SetfTimeSinceLastSpawn(float time)
{
    this->fTimeSinceLastSpawn = time;
}

void Train::Update(float fElapsed)
{
    this->posX += (int)(fElapsed * this->velocity * CellSize);
}

void Train::DrawFromLeftToRight(int x0, int y0, int x1, int y1)
{
    if (x0 >= render_state.width) return;
    if (y0 >= render_state.height) return;

    int dx;
    if (x0 < 0) dx = 0 - x0;
    else dx = 0;

    clip(x0, y0);
    clip(x1, y1);

    for (int y = y0; y < y1; y++)
    {
        unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;

        for (int x = x0; x < x1; x++)
        {
            int idx = 720 * (80 - (y - y0) - 1) + dx + (x - x0);
            *pixel++ = this->picture[idx];
        }
    }
}

void Train::DrawFromRightToLeft(int x0, int y0, int x1, int y1)
{
    if (x0 >= render_state.width) return;
    if (y0 >= render_state.height) return;

    int dx;
    if (x0 < 0) dx = 0 - x0;
    else dx = 0;

    clip(x0, y0);
    clip(x1, y1);

    for (int y = y0; y < y1; y++)
    {
        unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;

        for (int x = x0; x < x1; x++)
        {
            int idx = 720 * (80 - (y - y0) - 1) + dx + (x - x0);
            *pixel++ = this->SymmetricPicture[idx];
        }
    }
}
