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

void draw_text(string text, int StartX, int StartY, unsigned int color)
{
    int TextSize = 5;

    for (int i = 0; i < text.size(); i++)
    {
        string letter[7];
        int idx = 0;

        if ('A' <= text[i] && text[i] <= 'Z')
        {
            for (int row = (text[i] - 'A') * 7; row < (text[i] - 'A') * 7 + 7; row++)
            {
                letter[idx] = letters[row];
                idx++;
            }
        }
        else
        {
            for (int row = (text[i] - '0' + 26) * 7; row < (text[i] - '0' + 26) * 7 + 7; row++)
            {
                letter[idx] = letters[row];
                idx++;
            }
        }
        
        for (int j = 6; j >= 0; j--)
        {
            int StartPosX = StartX + TextSize * 7 * i;
            int StartPosY = StartY + (6 - j) * TextSize;

            for (char c : letter[j])
            {
                if (c == '0')
                    draw_rectangle(StartPosX, StartPosY, StartPosX + TextSize, StartPosY + TextSize, color);
                StartPosX += TextSize;
            }
        }
    }
}

bool simulate_game(HDC hdc, Input* input, float fTimeSinceStart, float fElapsedTime, 
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
    else if (pressed(BUTTON_ENTER)) 
    {
        running = false;
        return false;
    }


    if (playerX < 0) playerX = 0;
    if (playerX > render_state.width - CellSize) playerX = render_state.width - CellSize;
    if (playerY < 0) playerY = 0;
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
                        if (vecTrain[i]->GetfTimeSinceLastSpawn() >= abs(train_velocity))
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
                        if (vecTrain[i]->GetfTimeSinceLastSpawn() >= abs(train_velocity))
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
    {/*
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
        return true; */
        return true;
    }
    else if (playerY >= CellSize * 8)
    {
        for (int i = 0; i < vecTrain.size(); i++)
        {
            delete vecTrain[i];
            delete vecLight[i];
            vecTrain[i] = nullptr;
            vecLight[i] = nullptr;
        }

        vecTrain.clear();
        vecLight.clear();

        generateMap(player->GetLevel());

        int y = 8;
        int idx = 0;

        for (auto lane : vecLanes)
        {
            float velocity = lane.first;
            if (LOWER_BOUND_TRAIN + player->GetLevel() <= abs(velocity) && abs(velocity) <= UPPER_BOUND_TRAIN + player->GetLevel())
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
                        vecLight.push_back(new TrafficLight("trafficlight2.txt", "trafficlight1.txt", RED_LIGHT, 0));
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

void RunGameLoop(HDC hdc, int dem)
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
    generateMap(player.GetLevel());

    vector<Train*> vecTrain;
    vector<TrafficLight*> vecLight;

    int y = 8;
    int idx = 0;
    for (auto lane : vecLanes)
    {
        float velocity = lane.first;
        if (LOWER_BOUND_TRAIN + player.GetLevel() <= abs(velocity) && abs(velocity) <= UPPER_BOUND_TRAIN + player.GetLevel())
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
                    vecLight.push_back(new TrafficLight("trafficlight2.txt", "trafficlight1.txt", RED_LIGHT, 0));
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

    bool isSaveGame = false;
    string UserName;
    int size = 'Z' - 'A' + 1;
    Button_State* InputName = new Button_State[size];

    running = true;
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

        for (int i = 0; i < size; i++)
            InputName[i].changed = false;

        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            switch (message.message)
            {
            case WM_KEYUP:
            case WM_KEYDOWN:
            {
                unsigned int vk_code = (unsigned int)message.wParam;
                bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
input.buttons[b].changed = input.buttons[b].is_down != is_down;\
input.buttons[b].is_down = is_down;\
}; break;

                if (isSaveGame && 0x41 <= vk_code && vk_code <= 0x5A)
                {
                    InputName[vk_code - 0x41].changed = InputName[vk_code - 0x41].is_down != is_down;
                    InputName[vk_code - 0x41].is_down = is_down;
                    
                }
                else
                {
                    switch (vk_code)
                    {
                        process_button(BUTTON_UP, VK_UP);
                        process_button(BUTTON_DOWN, VK_DOWN);
                        process_button(BUTTON_LEFT, VK_LEFT);
                        process_button(BUTTON_RIGHT, VK_RIGHT);
                        process_button(BUTTON_ENTER, VK_RETURN);
                        process_button(BUTTON_ESCAPE, VK_ESCAPE);
                        process_button(BUTTON_BACKSPACE, VK_BACK);
                    }
                }
                


            } break;
            default:
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            } break;
            }
        }


        if (input.buttons[BUTTON_ESCAPE].is_down && input.buttons[BUTTON_ESCAPE].changed)
            isSaveGame = true;

        bool dead = false;
        if (isSaveGame)
        {
            // (input->buttons[b].is_down&& input->buttons[b].changed)
            for (int i = 0; i < size; i++)
            {
                if (InputName[i].is_down && InputName[i].changed)
                    UserName += i + 'A';
            }
            
            if (input.buttons[BUTTON_BACKSPACE].is_down && input.buttons[BUTTON_BACKSPACE].changed)
            {
                if (UserName.size() > 0)
                    UserName.pop_back();
            }
            
            if (input.buttons[BUTTON_ENTER].is_down && input.buttons[BUTTON_ENTER].changed)
            {
                saveToFile(UserName, player, fSinceStart);
                running = false;
            }

            clear_screen(0xf2c488);
            draw_text("USERNAME", 50, 360, 0x000000);
            draw_rectangle(330, 360, 335, 365, 0x00000);
            draw_rectangle(330, 375, 335, 380, 0x00000);
            draw_text(UserName, 350, 360, 0x000000);
        }
        else
        {
            fSinceStart += fElapsedTime;
            dead = simulate_game(hdc, &input, fSinceStart, fElapsedTime,
                &player, vecTrain, vecLight,
                &horse, &water, &log, &cactus, &bush, &rock, danger, &reverseHorseWagon);

            if (dead)
            {
                clear_screen(0xf2c488);
                draw_text("SCORE", 50, 360, 0x000000);
                draw_rectangle(400, 360, 410, 370, 0x000000);
                draw_rectangle(400, 400, 410, 410, 0x000000);
                string strScore = to_string((player.GetLevel()-1) * 100);
                draw_text(strScore, 450, 360, 0x000000);
            }

        }

        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height,
            0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info,
            DIB_RGB_COLORS, SRCCOPY);

        if (dead)
        {
            Sleep(3000);
            running = false;
        }
            
    }

    for (int i = 0; i < vecTrain.size(); i++)
    {
        delete vecTrain[i];
        delete vecLight[i];
    }

    vecTrain.resize(0);
    vecLight.resize(0);
    delete[] InputName;
    running = false;
}

void RunLoadGame(HDC hdc)
{
    bool isLoadGame = true;
    int size = 'Z' - 'A' + 1;
    Button_State* InputPath = new Button_State[size];
    Input input = {};
    string Path;
    float fSinceStart = 0;

    Player player("player.txt", 0, 0);
    while (isLoadGame)
    {
        for (int i = 0; i < BUTTON_COUNT; i++)
            input.buttons[i].changed = false;

        for (int i = 0; i < size; i++)
            InputPath[i].changed = false;

        MSG message;
        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            switch (message.message)
            {
            case WM_KEYUP:
            case WM_KEYDOWN:
            {
                unsigned int vk_code = (unsigned int)message.wParam;
                bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
input.buttons[b].changed = input.buttons[b].is_down != is_down;\
input.buttons[b].is_down = is_down;\
}; break;

                if (isLoadGame && 0x41 <= vk_code && vk_code <= 0x5A)
                {
                    InputPath[vk_code - 0x41].changed = InputPath[vk_code - 0x41].changed != is_down;
                    InputPath[vk_code - 0x41].is_down = is_down;
                }
                else
                {
                    switch (vk_code)
                    {
                        process_button(BUTTON_UP, VK_UP);
                        process_button(BUTTON_DOWN, VK_DOWN);
                        process_button(BUTTON_LEFT, VK_LEFT);
                        process_button(BUTTON_RIGHT, VK_RIGHT);
                        process_button(BUTTON_ENTER, VK_RETURN);
                        process_button(BUTTON_ESCAPE, VK_ESCAPE);
                        process_button(BUTTON_BACKSPACE, VK_BACK);
                    }
                }
                
            } break;
            default:
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            } break;
            }
        }
        bool isFalsePath = false;

        if (isLoadGame)
        {
            // (input->buttons[b].is_down&& input->buttons[b].changed)  
            for (int i = 0; i < size; i++)
            {
                if (InputPath[i].is_down && InputPath[i].changed)
                    Path += i + 'A';
            }

            if (input.buttons[BUTTON_BACKSPACE].is_down && input.buttons[BUTTON_BACKSPACE].changed)
            {
                if (Path.size() > 0)
                    Path.pop_back();
            }

            clear_screen(0xf2c488);
            draw_text("PATH", 50, 360, 0x000000);
            draw_rectangle(250, 360, 255, 365, 0x00000);
            draw_rectangle(250, 375, 255, 380, 0x00000);
            draw_text(Path, 350, 360, 0x000000);

            

            if (input.buttons[BUTTON_ENTER].is_down && input.buttons[BUTTON_ENTER].changed)
            {
                ifstream ifs(Path);
                if (ifs.good() == false)
                {
                    clear_screen(0xf2c488);
                    draw_text("UNDEFINED", 50, 360, 0x000000);
                    draw_text("PATH", 400, 360, 0x000000);
                    isFalsePath = true;
                }
                else
                {
                    readFromSave(Path, player, fSinceStart);
                    player.SetLastTimeOnLog(0);
                    ifs.close();
                }
                isLoadGame = false;
            }
        }
        
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height,
            0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info,
            DIB_RGB_COLORS, SRCCOPY);

        if (isFalsePath)
        {
            delete[] InputPath;
            Sleep(3000);
            running = false;
            return;
        }
    }

    delete[] InputPath;

    Sprite log("log.txt");
    Sprite rock("rock.txt");
    Sprite bush("bush.txt");
    Sprite cactus("cactus.txt");
    Sprite water("water.txt");
    Sprite horse("horsewagon.txt");
    Sprite reverseHorseWagon("reverseHorseWagon.txt");

    vector<Train*> vecTrain;
    vector<TrafficLight*> vecLight;

    int y = 8;
    int idx = 0;
    for (auto lane : vecLanes)
    {
        float velocity = lane.first;
        if (LOWER_BOUND_TRAIN + player.GetLevel() <= abs(velocity) && abs(velocity) <= UPPER_BOUND_TRAIN + player.GetLevel())
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

    bool isSaveGame = false;
    string UserName;
    Button_State* InputName = new Button_State[size];

    running = true;
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

        for (int i = 0; i < size; i++)
            InputName[i].changed = false;

        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            switch (message.message)
            {
            case WM_KEYUP:
            case WM_KEYDOWN:
            {
                unsigned int vk_code = (unsigned int)message.wParam;
                bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
input.buttons[b].changed = input.buttons[b].is_down != is_down;\
input.buttons[b].is_down = is_down;\
}; break;

                if (isSaveGame && 0x41 <= vk_code && vk_code <= 0x5A)
                {
                    InputName[vk_code - 0x41].changed = InputName[vk_code - 0x41].changed != is_down;
                    InputName[vk_code - 0x41].is_down = is_down;
                }
                else
                {
                    switch (vk_code)
                    {
                        process_button(BUTTON_UP, VK_UP);
                        process_button(BUTTON_DOWN, VK_DOWN);
                        process_button(BUTTON_LEFT, VK_LEFT);
                        process_button(BUTTON_RIGHT, VK_RIGHT);
                        process_button(BUTTON_ENTER, VK_RETURN);
                        process_button(BUTTON_ESCAPE, VK_ESCAPE);
                        process_button(BUTTON_BACKSPACE, VK_BACK);
                    }
                }



            } break;
            default:
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            } break;
            }
        }


        if (input.buttons[BUTTON_ESCAPE].is_down && input.buttons[BUTTON_ESCAPE].changed)
            isSaveGame = true;

        bool dead = false;
        if (isSaveGame)
        {
            // (input->buttons[b].is_down&& input->buttons[b].changed)
            for (int i = 0; i < size; i++)
            {
                if (InputName[i].is_down && InputName[i].changed)
                    UserName += i + 'A';
            }

            if (input.buttons[BUTTON_BACKSPACE].is_down && input.buttons[BUTTON_BACKSPACE].changed)
            {
                if (UserName.size() > 0)
                    UserName.pop_back();
            }

            if (input.buttons[BUTTON_ENTER].is_down && input.buttons[BUTTON_ENTER].changed)
            {
                saveToFile(UserName, player, fSinceStart);
                running = false;
            }

            clear_screen(0xf2c488);
            draw_text("USERNAME", 50, 360, 0x000000);
            draw_rectangle(330, 360, 335, 365, 0x00000);
            draw_rectangle(330, 375, 335, 380, 0x00000);
            draw_text(UserName, 350, 360, 0x000000);
        }
        else
        {
            fSinceStart += fElapsedTime;
            dead = simulate_game(hdc, &input, fSinceStart, fElapsedTime,
                &player, vecTrain, vecLight,
                &horse, &water, &log, &cactus, &bush, &rock, danger, &reverseHorseWagon);

            if (dead)
            {
                clear_screen(0xf2c488);
                draw_text("SCORE", 50, 360, 0x000000);
                draw_rectangle(350, 360, 360, 370, 0x000000);
                draw_rectangle(350, 400, 360, 410, 0x000000);
                string strScore = to_string((player.GetLevel()-1) * 100);
                draw_text(strScore, 400, 360, 0x000000);
            }
            delete[] danger;

        }

        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height,
            0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info,
            DIB_RGB_COLORS, SRCCOPY);

        if (dead)
        {
            Sleep(3000);
            running = false;
        }
    }

    for (int i = 0; i < vecTrain.size(); i++)
    {
        delete vecTrain[i];
        delete vecLight[i];
    }

    vecTrain.resize(0);
    vecLight.resize(0);
    delete[] InputName;
    running = false;
}

