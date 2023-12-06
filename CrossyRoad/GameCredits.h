#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include "Button.h"
#include "RectangleAndEllipse.h"
#include "GameMenu.h"

class GameCredits
{
private:
    HBITMAP hBackgroundBitmap;  // Bitmap for the background image
    HWND hwnd;                  // Window handle
    Button* buttons;

    // Other private member functions and variables can be placed here
    static HBITMAP LoadBitmapImage(const wchar_t* filename);
    void setButtonImage();
    void createButton();
    void DrawBackgroundWithButtons(HDC hdc);

public:
    GameCredits();
    ~GameCredits();
    void HandleCommand(int id);
    void Initialize(HWND hwnd);
    void OnPaint(HDC hdc, HWND hwnd);

    // Other member functions for handling window messages can be defined here
};

void RunCreditsLoop(HDC hdc, GameCredits* gameCredits, HWND hwnd);