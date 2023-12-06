#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include "Button.h"
#include "RectangleAndEllipse.h"
#include "SimulateGame.h"
#include "GameSettings.h"

class GameMenu
{
private:
    static constexpr int numButton = 5;
    HBRUSH hBackgroundBrush;    // Brush for the background color
    HBITMAP hBackgroundBitmap;  // Bitmap for the background image
    HWND hwnd;                  // Window handle
    Button *buttons[numButton]; // Array of buttons
    bool runningNewGame = false;
    bool runningLoadGame = false;
    bool runningSettings = false;
    bool runningCredits = false;

    // Other private member functions and variables can be placed here
    static HBITMAP LoadBitmapImage(const wchar_t* filename);
    void setButtonImage();
    void createAButton(int i);
    void OnButtonClick(const char* buttonName);
    void OnFileExit();
    void DrawBackgroundWithButtons(HDC hdc);

public:
    GameMenu();
    ~GameMenu();
    void setRunningNewGame(bool runningNewGame);
    void setRunningLoadGame(bool runningLoadGame);
    void setRunningSettings(bool runningSettings);
    void setRunningCredits(bool runningCredits);

    bool getRunningNewGame();
    bool getRunningLoadGame();
    bool getRunningSettings();
    bool getRunningCredits();

    void Initialize(HWND hwnd);
    void HandleCommand(int id);
    void OnPaint(HDC hdc, HWND hwnd);

    // Other member functions for handling window messages can be defined here
};