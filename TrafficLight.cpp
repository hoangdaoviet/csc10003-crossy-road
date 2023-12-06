#include "TrafficLight.h"
#include <fstream>

unsigned int TrafficLight::convertToHex(string s)
{
    unsigned int ans = 0;
    unsigned int heso = 1;

    for (int i = s.size() - 1; i >= 0; i--)
    {
        int sohang;
        if ('0' <= s[i] && s[i] <= '9')
            sohang = s[i] - '0';
        else if (s[i] == 'A')
            sohang = 10;
        else if (s[i] == 'B')
            sohang = 11;
        else if (s[i] == 'C')
            sohang = 12;
        else if (s[i] == 'D')
            sohang = 13;
        else if (s[i] == 'E')
            sohang = 14;
        else if (s[i] == 'F')
            sohang = 15;

        ans += sohang * heso;
        heso *= 16;
    }

    return ans;
}

vector<unsigned int> TrafficLight::GetPicture(string fileName)
{
    ifstream ifs;
    ifs.open(fileName);
    vector<unsigned int> result;

    if (!ifs.is_open())
    {
        cout << "Error opening file !!! \n";
        return result;
    }

    while (!ifs.eof())
    {
        string tmp;
        ifs >> tmp;
        if (tmp[0] == '#')
        {
            tmp.erase(0, 1);
            result.push_back(convertToHex(tmp));
        }
    }

    ifs.close();
    return result;
}

void TrafficLight::clip(int& x, int& y)
{
    if (x < 0) x = 0;
    if (x >= render_state.width) x = render_state.width - 1;
    if (y < 0) y = 0;
    if (y >= render_state.height) y = render_state.height - 1;

}
TrafficLight::TrafficLight()
{

}

TrafficLight::TrafficLight(string RedLight, string GreenLight, int state, float fTimeSinceLastLight)
{
    this->RedLight = GetPicture(RedLight);
    this->GreenLight = GetPicture(GreenLight);
	this->state = state;
}

void TrafficLight::SetState(int state)
{
	this->state = state;
}

void TrafficLight::SetPosition(int x, int y)
{
    this->posX = x;
    this->posY = y;
}

void TrafficLight::SetfTimeSinceLastLight(float time)
{
    this->fTimeSinceLastLight = time;
}

int TrafficLight::GetPosX()
{
    return this->posX;
}

int TrafficLight::GetPosY()
{
    return this->posY;
}

int TrafficLight::GetState()
{
	return this->state;
}

float TrafficLight::GetfTimeSinceLastLight()
{
    return this->fTimeSinceLastLight;
}

void TrafficLight::DrawRedLight(int x0, int y0, int x1, int y1)
{
    int dx;
    if (x0 < 0) dx = 0 - x0;
    else dx = 0;

    clip(x0, y0);
    clip(x1, y1);

    if (this->RedLight.size() <= 6400)
    {
        int width = x1 - x0;
        for (int y = y0; y < y1; y++)
        {
            unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;

            for (int x = x0; x < x1; x++)
            {
                int idx = 80 * (80 - (y - y0) - 1) + dx + (x - x0);
                if (RedLight[idx] == 0xF2C488)
                    pixel++;
                else
                    *pixel++ = RedLight[idx];
            }
        }
    }
}

void TrafficLight::DrawGreenLight(int x0, int y0, int x1, int y1)
{
    int dx;
    if (x0 < 0) dx = 0 - x0;
    else dx = 0;

    clip(x0, y0);
    clip(x1, y1);

    if (this->GreenLight.size() <= 6400)
    {
        int width = x1 - x0;
        for (int y = y0; y < y1; y++)
        {
            unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;

            for (int x = x0; x < x1; x++)
            {
                int idx = 80 * (80 - (y - y0) - 1) + dx + (x - x0);

                if (GreenLight[idx] == 0xF2C488)
					pixel++;
				else
					*pixel++ = GreenLight[idx];
            }
        }
    }
}

void TrafficLight::UpdateState(float fElapsedTime)
{
    this->fTimeSinceLastLight += fElapsedTime;
    if (this->fTimeSinceLastLight >= 5)
    {
        if (this->state == RED_LIGHT)
            this->state = GREEN_LIGHT;
        else
            this->state = RED_LIGHT;

        this->fTimeSinceLastLight = 0;
    }
        
}

void TrafficLight::Draw(int x0, int y0, int x1, int y1)
{
    switch (this->state)
    {
        case RED_LIGHT: this->DrawRedLight(x0, y0, x1, y1); break;
        case GREEN_LIGHT: this->DrawGreenLight(x0, y0, x1, y1); break;
    }
}