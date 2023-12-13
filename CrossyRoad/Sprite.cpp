#include "Sprite.h"

unsigned int Sprite::convertToHex(string s)
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

    // Convert hexadecimal string to decimal number
    // ans = stoul(s, nullptr, 16);
    return ans;
}

vector<unsigned int> Sprite::GetPicture(string fileName)
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

void Sprite::clip(int& x, int& y)
{
    if (x < 0) x = 0;
    if (x >= render_state.width) x = render_state.width - 1;
    if (y < 0) y = 0;
    if (y >= render_state.height) y = render_state.height - 1;
}

Sprite::Sprite()
{

}

Sprite::Sprite(string fileName)
{
    this->picture = GetPicture(fileName);
}

void Sprite::Draw1stPartSpriteAt(int x0, int y0, int x1, int y1)
{
    if (x0 >= render_state.width) return;
    if (y0 >= render_state.height) return;
 
    int dx;
    if (x0 < 0) dx = 0 - x0;
    else dx = 0;

    clip(x0, y0);
    clip(x1, y1);
    
    if (this->picture.size() <= 6400)
    {
        int width = x1 - x0;
        for (int y = y0; y < y1; y++)
        {
            unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;
            
            for (int x = x0; x < x1; x++)
            {
                int idx = 80 * (80 - (y - y0) - 1) + dx + (x - x0);
                *pixel++ = picture[idx];
            }
        }
    }
    else
    {
        for (int y = y0; y < y1; y++)
        {
            unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;

            for (int x = x0; x < x1; x++)
            {
                int idx = 160 * (80 - (y - y0) - 1) + dx + (x - x0);
                *pixel++ = picture[idx];
            }
        }
    }
}

void Sprite::Draw2ndPartSpriteAt(int x0, int y0, int x1, int y1)
{
    if (x0 >= render_state.width) return;
    if (y0 >= render_state.height) return;
    if (this->picture.size() <= 6400)
        return;

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
            int idx = 80 + dx + 160 * (80 - (y - y0) - 1) + (x - x0);
            *pixel++ = picture[idx];
        }
    }
}