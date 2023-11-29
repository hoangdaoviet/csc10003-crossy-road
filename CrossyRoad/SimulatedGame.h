#pragma once
#ifndef _SIMULATED_GAME_H_
#define _SIMULATED_GAME_H_
#include "utility.h"
#include "Sprite.h"
#include "player.h"

using namespace std;

bool simulate_game(Input* input, float fSinceStart, float fElapsedTime, Player* player, Sprite* horse, Sprite* water, Sprite* log, Sprite* deadbush, Sprite* cactus, Sprite* bush, Sprite* rock, Sprite* highrock, bool* danger, Sprite* reverseHorseWagon);
void FillDanger(bool* danger, int x0, int y0, int x1, int y1);
void RunGameLoop(HDC hdc)
{
    Input input = {};
    // Initialize game objects and other necessary variables here
    Sprite log("log.txt");
    Sprite rock("rock.txt");
    Sprite bush("bush.txt");
    Sprite cactus("cactus.txt");
    Sprite highrock("highrock.txt");
    Sprite deadbush("deadbush.txt");
    Sprite water("water.txt");
    Sprite horse("horsewagon.txt");
    Sprite reverseHorseWagon("reverseHorseWagon.txt");
    Player player("player.txt", 80 * 8, 0);
    generateMap();

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();
    float fSinceStart = 0.0f;

    // Main game loop
    while (running) {
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> ElapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = ElapsedTime.count();

        bool* danger;
        danger = new bool[render_state.width * render_state.height];

        for (int i = 0; i < render_state.width * render_state.height; i++)
            danger[i] = false;

        MSG message;
        for (int i = 0; i < BUTTON_COUNT; i++)
            input.buttons[i].changed = false;

        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            switch (message.message)
            {
            case WM_KEYUP:
            case WM_KEYDOWN:
            {
                unsigned int vk_code = (unsigned int)message.wParam;
                bool is_down = ((message.lParam & (1 << 31)) == 0);

                switch (vk_code)
                {
                case VK_UP: {
                    input.buttons[BUTTON_UP].changed = is_down != input.buttons[BUTTON_UP].is_down;
                    input.buttons[BUTTON_UP].is_down = is_down;

                } break;
                case VK_DOWN: {
                    input.buttons[BUTTON_DOWN].changed = is_down != input.buttons[BUTTON_DOWN].is_down;
                    input.buttons[BUTTON_DOWN].is_down = is_down;
                } break;
                case VK_LEFT: {
                    input.buttons[BUTTON_LEFT].changed = is_down != input.buttons[BUTTON_LEFT].is_down;
                    input.buttons[BUTTON_LEFT].is_down = is_down;
                } break;
                case VK_RIGHT: {
                    input.buttons[BUTTON_RIGHT].changed = is_down != input.buttons[BUTTON_RIGHT].is_down;
                    input.buttons[BUTTON_RIGHT].is_down = is_down;
                } break;
                case VK_RETURN: {
                    input.buttons[BUTTON_ENTER].changed = is_down != input.buttons[BUTTON_ENTER].is_down;
                    input.buttons[BUTTON_ENTER].is_down = is_down;
                } break;

                }

            } break;

            default: {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            }

        }



        // Process input, simulate game, and render
        fSinceStart += fElapsedTime;
        bool dead = simulate_game(&input, fSinceStart, fElapsedTime, &player, &horse, &water, &log, &deadbush, &cactus, &bush, &rock, &highrock, danger, &reverseHorseWagon);

        // ... (your existing game logic)

        // Render only when needed
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

        // Cleanup
        if (dead)
            Sleep(1000);
        delete[] danger;
    }
}

void clip(int& x, int& y)
{
    if (x < 0) x = 0;
    if (x > render_state.width) x = render_state.width;
    if (y < 0) y = 0;
    if (y > render_state.height) y = render_state.height;
}

void clear_screen(unsigned int color)
{
    unsigned int* pixel = (unsigned int*)render_state.memory;

    for (int y = 0; y < render_state.height; y++)
        for (int x = 0; x < render_state.width; x++)
            *pixel++ = color;
}

void draw_rectangle(int x0, int y0, int x1, int y1, unsigned int color)
{
    clip(x0, y0);
    clip(x1, y1);

    for (int y = y0; y < y1; y++)
    {
        unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;
        for (int x = x0; x < x1; x++)
        {
            *pixel++ = color;
        }
    }
}

void draw_player(int x0, int y0, int x1, int y1, vector<unsigned int>& player)
{
    clip(x0, y0);
    clip(x1, y1);

    int idx = 0;
    for (int y = y0; y < y1; y++)
    {
        unsigned int* pixel = (unsigned int*)render_state.memory + y * render_state.width + x0;
        for (int x = x0; x < x1; x++)
        {
            *pixel++ = player[idx];
            idx++;
        }
    }
}

#define is_down(b) input->buttons[b].is_down
#define	pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define	released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

void FillDanger(bool* danger, int x0, int y0, int x1, int y1)
{
    clip(x0, y0);
    clip(x1, y1);

    for (int y = y0; y < y1; y++)
        for (int x = x0; x < x1; x++)
            danger[y * render_state.width + x] = true;
}

bool simulate_game(Input* input, float fTimeSinceStart, float fElapsedTime, Player* player, Sprite* horse, Sprite* water, Sprite* log, Sprite* deadbush, Sprite* cactus, Sprite* bush, Sprite* rock, Sprite* highrock, bool* danger, Sprite* reverseHorseWagon)
{
    clear_screen(0xF2C488);

    int old_playerX = player->GetPosX();
    int old_playerY = player->GetPosY();

    int playerX = player->GetPosX();
    int playerY = player->GetPosY();

    if (pressed(BUTTON_UP))
    {
        player->SetLastTimeOnLog(0);
        playerY += CellSize;
    }
    else if (pressed(BUTTON_DOWN))
    {
        player->SetLastTimeOnLog(0);
        playerY -= CellSize;
    }
    else if (pressed(BUTTON_LEFT))
    {
        playerX -= CellSize;
    }
    else if (pressed(BUTTON_RIGHT))
    {
        playerX += CellSize;
    }
    else if (pressed(BUTTON_ENTER)) {
        running = false;
        return false;
    }

    if (playerX < 0) playerX = 0;
    if (playerX > render_state.width - CellSize) playerX = render_state.width - CellSize;
    if (playerX < 0) playerY = 0;
    if (playerY > render_state.height - CellSize - 1) playerY = render_state.height - CellSize;

    bool isOnLog = false;
    int curLane = 8 - playerY / CellSize;

    for (char c : vecLanes[curLane].second)
    {
        if (c == 'l')
        {
            isOnLog = true;
            break;
        }
    }

    if (isOnLog == true)
    {
        float velocity = vecLanes[curLane].first;

        if (player->GetLastTimeOnLog() != 0)
        {
            int dx = (int)(fTimeSinceStart * velocity * CellSize) - (int)(player->GetLastTimeOnLog() * velocity * CellSize);
            playerX += dx;
            player->SetLastTimeOnLog(fTimeSinceStart);

            if (playerX < 0 || playerX >= render_state.width - CellSize)
            {
                playerX = 80 * 8;
                playerY = 0;
                player->SetLastTimeOnLog(0);
            }
        }
        else
        {
            for (int i = 0; i < vecLanes[curLane].second.size(); i++)
            {
                int StartPosX = i * CellSize + (int)(fTimeSinceStart * velocity * CellSize);

                if (StartPosX < 0) StartPosX = render_state.width - (abs(StartPosX) % (render_state.width + CellSize));
                else StartPosX = StartPosX % (render_state.width + CellSize) - CellSize;

                if ((StartPosX <= playerX && playerX < StartPosX + CellSize)
                    || (StartPosX <= (playerX + CellSize - 1) && (playerX + CellSize - 1) < StartPosX + CellSize))
                    playerX = StartPosX;
            }
            player->SetLastTimeOnLog(fTimeSinceStart);
        }
    }
    else
    {
        player->SetLastTimeOnLog(0);
        playerX = playerX / CellSize * CellSize;
    }

    int y = 8;
    for (auto lane : vecLanes)
    {
        float velocity = lane.first;
        for (int i = 0; i < lane.second.length(); i++)
        {
            int StartPosX;
            int StartPosY;

            if (velocity == 0)
            {
                StartPosX = i * CellSize;
                StartPosY = y * CellSize;
            }
            else
            {
                StartPosX = i * CellSize + (int)(fTimeSinceStart * velocity * CellSize);
                StartPosY = y * CellSize;

                if (StartPosX < 0) StartPosX = render_state.width - (abs(StartPosX) % (render_state.width + CellSize));
                else StartPosX = StartPosX % (render_state.width + CellSize) - CellSize;
            }

            switch (lane.second[i])
            {
            case 'r':
            {
                rock->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            case 'h':
            {
                if (velocity < 0)
                    reverseHorseWagon->Draw2ndPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
                else
                    horse->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
                FillDanger(danger, StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            case 'H':
            {
                if (velocity < 0)
                    reverseHorseWagon->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
                else
                    horse->Draw2ndPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
                FillDanger(danger, StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            case 'l':
            {
                log->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            case 'c':
            {
                cactus->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            case 'b':
            {
                bush->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            case 'd':
            {
                deadbush->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            case '~':
            {
                water->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
                FillDanger(danger, StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            }
        }

        y = y - 1;
    }

    bool move_collision = ((vecLanes[curLane].second[playerX / 80 % 19] == 'b')
        // || (vecLanes[8 - (next_posY / 80)].second[next_posX / 80 % 16] == 'h')
        || (vecLanes[curLane].second[playerX / 80 % 19] == 'd')
        || (vecLanes[curLane].second[playerX / 80 % 19] == 'r')
        || (vecLanes[curLane].second[playerX / 80 % 19] == 'c'));

    bool bl = danger[playerY * render_state.width + playerX];
    bool br = danger[playerY * render_state.width + playerX + CellSize - 2];
    bool tl = danger[(playerY + CellSize - 1) * render_state.width + playerX];
    bool tr = danger[(playerY + CellSize - 1) * render_state.width + playerX + CellSize - 2];

    bool dead_collision = bl || br || tl || tr;

    if (move_collision)
    {
        player->SetPosition(old_playerX, old_playerY);
        player->DrawPlayer(old_playerX, old_playerY, old_playerX + CellSize, old_playerY + CellSize);
    }
    else if (dead_collision)
    {
        player->DrawPlayer(playerX, playerY, playerX + CellSize, playerY + CellSize);
        player->SetPosition(80 * 8, 0);
        player->SetLastTimeOnLog(0);
        return true;
    }
    else if (playerY >= CellSize * 8)
    {
        generateMap();
        player->SetPosition(80 * 8, 0);
    }
    else
    {
        player->SetPosition(playerX, playerY);
        player->DrawPlayer(playerX, playerY, playerX + CellSize, playerY + CellSize);
    }

    return false;
}

#endif