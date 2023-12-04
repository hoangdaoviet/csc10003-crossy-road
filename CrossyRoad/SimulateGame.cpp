#include "SimulateGame.h"

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

void FillDanger(bool* danger, int x0, int y0, int x1, int y1)
{
    clip(x0, y0);
    clip(x1, y1);

    for (int y = y0; y < y1; y++)
        for (int x = x0; x < x1; x++)
            danger[y * render_state.width + x] = true;
}

bool simulate_game(Input* input, float fTimeSinceStart, float fElapsedTime, 
    Player* player, vector<Train*> &vecTrain, vector<TrafficLight*> &vecLight,
    Sprite* horse, Sprite* water, Sprite* log, Sprite* cactus, Sprite* bush, Sprite* rock, bool* danger, Sprite* reverseHorseWagon)
{
    clear_screen(0xF2C488);

    int old_playerX = player->GetPosX();
    int old_playerY = player->GetPosY();

    int playerX = player->GetPosX();
    int playerY = player->GetPosY();
    int playerLevel = player->GetLevel();

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
                if (vecLanes[curLane].second[i] == 'l')
                {
                    int StartPosX = i * CellSize + (int)(fTimeSinceStart * velocity * CellSize);

                    if (StartPosX < 0) StartPosX = render_state.width - (abs(StartPosX) % (render_state.width + CellSize));
                    else StartPosX = StartPosX % (render_state.width + CellSize) - CellSize;

                    if ((StartPosX <= playerX + CellSize / 4 && playerX + CellSize / 4 < StartPosX + CellSize)
                        || (StartPosX <= (playerX + CellSize * 3 / 4) && (playerX + CellSize * 3 / 4) < StartPosX + CellSize))
                        playerX = StartPosX;
                }
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
            case '~':
            {
                water->Draw1stPartSpriteAt(StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
                FillDanger(danger, StartPosX, StartPosY, StartPosX + CellSize, StartPosY + CellSize);
            } break;
            }
        }

        y = y - 1;
    }

    int size = vecTrain.size();
    for (int i = 0; i < size; i++)
    {
        int train_posX = vecTrain[i]->GetPosX();
        int train_posY = vecTrain[i]->GetPosY();
        float train_velocity = vecTrain[i]->GetVelocity();

        int light_posX = vecLight[i]->GetPosX();
        int light_state = vecLight[i]->GetState();

        if (train_velocity > 0)
        {
            if (train_posX + 720 < light_posX - CellSize / 4)
            {
                light_state = RED_LIGHT;

                vecTrain[i]->Update(fElapsedTime);
                train_posX = vecTrain[i]->GetPosX();
            }
            else
            {
                if (light_state == RED_LIGHT)
                {
                    if (vecTrain[i]->GetfTimeStop() >= 5)
                    {
                        light_state = GREEN_LIGHT;
                        vecTrain[i]->Update(fElapsedTime);
                        train_posX = vecTrain[i]->GetPosX();
                    }
                    else
                        vecTrain[i]->SetfTimeStop(vecTrain[i]->GetfTimeStop() + fElapsedTime);
                }
                else
                {
                    vecTrain[i]->Update(fElapsedTime);
                    train_posX = vecTrain[i]->GetPosX();

                    if (train_posX >= render_state.width)
                    {
                        if (vecTrain[i]->GetfTimeSinceLastSpawn() >= 5)
                        {
                            train_posX = 0 - 2 * train_velocity * CellSize;
                            vecTrain[i]->SetPosition(train_posX, train_posY);
                            vecTrain[i]->SetfTimeSinceLastSpawn(0);
                            vecTrain[i]->SetfTimeStop(0);
                            light_state = RED_LIGHT;
                        }
                        else
                        {
                            vecTrain[i]->SetfTimeSinceLastSpawn(vecTrain[i]->GetfTimeSinceLastSpawn() + fElapsedTime);
                        }

                    }
                }
            }
        }
        else
        {
            if (light_posX + CellSize * 5 / 4 <= train_posX)
            {
                light_state = RED_LIGHT;

                vecTrain[i]->Update(fElapsedTime);
                train_posX = vecTrain[i]->GetPosX();
            }
            else
            {
                if (light_state == RED_LIGHT)
                {
                    if (vecTrain[i]->GetfTimeStop() >= 5)
                    {
                        light_state = GREEN_LIGHT;
                        vecTrain[i]->Update(fElapsedTime);
                        train_posX = vecTrain[i]->GetPosX();
                    }
                    else
                        vecTrain[i]->SetfTimeStop(vecTrain[i]->GetfTimeStop() + fElapsedTime);
                }
                else
                {
                    vecTrain[i]->Update(fElapsedTime);
                    train_posX = vecTrain[i]->GetPosX();

                    if (train_posX <= 0)
                    {
                        if (vecTrain[i]->GetfTimeSinceLastSpawn() >= 5)
                        {
                            train_posX = render_state.width - 2 * train_velocity * CellSize;
                            vecTrain[i]->SetPosition(train_posX, train_posY);
                            vecTrain[i]->SetfTimeSinceLastSpawn(0);
                            vecTrain[i]->SetfTimeStop(0);
                            light_state = RED_LIGHT;
                        }
                        else
                        {
                            vecTrain[i]->SetfTimeSinceLastSpawn(vecTrain[i]->GetfTimeSinceLastSpawn() + fElapsedTime);
                        }
                    }
                }
            }
        }

        vecLight[i]->SetState(light_state);

        if (train_velocity < 0)
            vecTrain[i]->DrawFromLeftToRight(train_posX, train_posY, train_posX + 720, train_posY + 80);
        else
            vecTrain[i]->DrawFromRightToLeft(train_posX, train_posY, train_posX + 720, train_posY + 80);
        
        FillDanger(danger, train_posX, train_posY, train_posX + 720, train_posY + 80);
        vecLight[i]->Draw(light_posX, train_posY, light_posX + 80, train_posY + 80);
    }

    bool move_collision = ((vecLanes[curLane].second[playerX / 80 % 19] == 'b')
        // || (vecLanes[8 - (next_posY / 80)].second[next_posX / 80 % 16] == 'h')
        || (vecLanes[curLane].second[playerX / 80 % 19] == 'd')
        || (vecLanes[curLane].second[playerX / 80 % 19] == 'r')
        || (vecLanes[curLane].second[playerX / 80 % 19] == 'c'));

    bool bl = danger[playerY * render_state.width + playerX + 2];
    bool br = danger[playerY * render_state.width + playerX + CellSize - 2];
    bool tl = danger[(playerY + CellSize - 1) * render_state.width + playerX + 2];
    bool tr = danger[(playerY + CellSize - 1) * render_state.width + playerX + CellSize - 2];

    bool dead_collision = bl || br || tl || tr;

    if (move_collision)
    {
        player->SetPosition(old_playerX, old_playerY);
        player->DrawPlayer(old_playerX, old_playerY, old_playerX + CellSize, old_playerY + CellSize);
    }
    else if (dead_collision)
    {
        int size = vecTrain.size();

        for (int i = 0; i < size; i++)
        {
            float velocity = vecTrain[i]->GetVelocity();
            vecTrain[i]->SetfTimeSinceLastSpawn(0);
            vecTrain[i]->SetfTimeStop(0);

            if (velocity > 0)
                vecTrain[i]->SetPosition(0 - 2 * velocity * CellSize, vecTrain[i]->GetPosY());
            else
                vecTrain[i]->SetPosition(render_state.width - 2 * velocity * CellSize, vecTrain[i]->GetPosY());
        }

        player->DrawPlayer(playerX, playerY, playerX + CellSize, playerY + CellSize);
        player->SetPosition(80 * 8, 0);
        player->SetLastTimeOnLog(0);
        return true;
    }
    else if (playerY >= CellSize * 8)
    {
        for (int i = 0; i < vecTrain.size(); i++)
        {
            delete vecTrain[i];
            delete vecLight[i];
        }

        vecTrain.clear();
        vecLight.clear();

        generateMap();

        int y = 8;
        int idx = 0;

        for (auto lane : vecLanes)
        {
            float velocity = lane.first;
            if (LOWER_BOUND_TRAIN <= abs(velocity) && abs(velocity) <= UPPER_BOUND_TRAIN)
            {
                if (velocity > 0)
                    vecTrain.push_back(new Train("train.txt", 0 - 2 * velocity * CellSize, y * CellSize));
                else
                    vecTrain.push_back(new Train("train.txt", render_state.width - 2 * velocity * CellSize, y * CellSize));

                vecTrain[idx]->SetfTimeStop(0);
                vecTrain[idx]->SetfTimeSinceLastSpawn(0);
                vecTrain[idx]->SetVelocity(velocity);

                for (int i = 0; i < lane.second.length(); i++)
                {
                    if (lane.second[i] == 'p')
                    {
                        vecLight.push_back(new TrafficLight("trafficlight.txt", "trafficlight.txt", RED_LIGHT, 0));
                        vecLight[idx]->SetfTimeSinceLastLight(0);
                        vecLight[idx]->SetPosition(i * CellSize, y * CellSize);
                        break;
                    }
                }
                idx++;
            }
            y--;
        }
        player->IncrementLevel();

        player->SetPosition(80 * 8, 0);
    }
    else
    {
        player->SetPosition(playerX, playerY);
        player->DrawPlayer(playerX, playerY, playerX + CellSize, playerY + CellSize);
    }

    return false;
}

void RunGameLoop(HDC hdc)
{
    Input input = {};
    // Initialize game objects and other necessary variables here
    Sprite log("log.txt");
    Sprite rock("rock.txt");
    Sprite bush("bush.txt");
    Sprite cactus("cactus.txt");
    Sprite water("water.txt");
    Sprite horse("horsewagon.txt");
    Sprite reverseHorseWagon("reverseHorseWagon.txt");

    Player player("player.txt", 80 * 8, 0);
    generateMap();

    vector<Train*> vecTrain;
    vector<TrafficLight*> vecLight;

    int y = 8;
    int idx = 0;
    for (auto lane : vecLanes)
    {
        float velocity = lane.first;
        if (LOWER_BOUND_TRAIN <= abs(velocity) && abs(velocity) <= UPPER_BOUND_TRAIN)
        {
            if (velocity > 0)
                vecTrain.push_back(new Train("train.txt", 0 - 2 * velocity * CellSize, y * CellSize));
            else
                vecTrain.push_back(new Train("train.txt", render_state.width - 2 * velocity * CellSize, y * CellSize));

            vecTrain[idx]->SetfTimeStop(0);
            vecTrain[idx]->SetfTimeSinceLastSpawn(0);
            vecTrain[idx]->SetVelocity(velocity);

            for (int i = 0; i < lane.second.length(); i++)
            {
                if (lane.second[i] == 'p')
                {
                    vecLight.push_back(new TrafficLight("trafficlight.txt", "trafficlight.txt", RED_LIGHT, 0));
                    vecLight[idx]->SetfTimeSinceLastLight(0);
                    vecLight[idx]->SetPosition(i * CellSize, y * CellSize);
                    break;
                }
            }
            idx++;
        }
        y--;
    }

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
        bool dead = simulate_game(&input, fSinceStart, fElapsedTime, 
            &player, vecTrain, vecLight,
            &horse, &water, &log, &cactus, &bush, &rock, danger, &reverseHorseWagon);

        // ... (your existing game logic)

        // Render only when needed
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

        // Cleanup
        if (dead)
            Sleep(1000);
        delete[] danger;
    }

    for (int i = 0; i < vecTrain.size(); i++)
    {
        delete vecTrain[i];
        delete vecLight[i];
    }

    vecTrain.resize(0);
    vecLight.resize(0);
}