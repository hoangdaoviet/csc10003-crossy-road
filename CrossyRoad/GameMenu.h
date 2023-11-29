#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_
#include <windows.h>
#include <string>
#include <iostream>
#include "Button.h"
#include "RectangleAndEllipse.h"
#include "SimulatedGame.h"

class GameMenu
{
private:
    static constexpr int numButton = 5;
    HBRUSH hBackgroundBrush;    // Brush for the background color
    HBITMAP hBackgroundBitmap;  // Bitmap for the background image
    HWND hwnd;                  // Window handle
    Button *buttons[numButton]; // Array of buttons
    bool runningNewGame = false;

    // Other private member functions and variables can be placed here

    static HBITMAP LoadBitmapImage(const wchar_t *filename)
    {
        return (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }

    void setButtonImage()
    {
        buttons[0] = new Button(new RectangleShape(), LoadBitmapImage(L"NEWGAME.bmp"));
        buttons[1] = new Button(new RectangleShape(), LoadBitmapImage(L"LOADGAME.bmp"));
        buttons[2] = new Button(new RectangleShape(), LoadBitmapImage(L"SETTINGS.bmp"));
        buttons[3] = new Button(new RectangleShape(), LoadBitmapImage(L"CREDITS.bmp"));
        buttons[4] = new Button(new RectangleShape(), LoadBitmapImage(L"EXIT.bmp"));
        // Add more buttons with different shapes as needed
    }

    void createAButton(int i)
    {
        int xPosition = 200;
        int yPosition = 250 + i * 80;

        // Load the image
        HBITMAP buttonImage = buttons[i]->GetImage();
        int buttonWidth = buttons[i]->getWidth();
        int buttonHeight = buttons[i]->getHeight();
        if (buttonImage == NULL)
        {
            MessageBox(NULL, L"Image Loading Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        HWND hButton = CreateWindow(
            L"BUTTON",                          // Button control
            L"button",                          // No text for the button
            WS_VISIBLE | WS_CHILD | BS_BITMAP, // Styles
            xPosition,                         // x position
            yPosition,                         // y position
            buttonWidth,                       // Button width
            buttonHeight,                      // Button height
            hwnd,                              // Parent window
            (HMENU)i,                          // No menu.
            NULL,
            NULL); // No additional data.

        if (hButton)
        {
            // Set the button's image
            SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)buttonImage);
        }
        else
        {
            MessageBox(NULL, L"Button Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        }
    }

    void OnButtonClick(const char *buttonName)
    {
        // Handle button click event
        std::ostringstream message;
        message << buttonName << "";
        MessageBox(hwnd,L"", L"", MB_OK);
    }

    void OnFileExit()
    {
        // Handle file exit event
        if (MessageBox(hwnd, L"Do you want to exit game ?", L"", MB_OKCANCEL) == IDOK)
            PostMessage(hwnd, WM_CLOSE, 0, 0);
    }

    void DrawBackgroundWithButtons(HDC hdc)
    {
        RECT rect;
        GetClientRect(hwnd, &rect);

        // Create a memory device context for the background
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMem, hBackgroundBitmap);

        // Draw the background bitmap onto the window
        BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcMem, 0, 0, SRCCOPY);

        // Clean up
        SelectObject(hdcMem, hBitmapOld);
        DeleteDC(hdcMem);
    }

public:
    GameMenu()
    {
        // Initialize variables and load resources
        hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 255));
        hBackgroundBitmap = LoadBitmapImage(L"crossyroad.bmp");
        setButtonImage();
        // Initialize other variables or perform additional setup if needed
    }

    ~GameMenu()
    {
        // Release resources, delete buttons, and perform cleanup
        DeleteObject(hBackgroundBrush);
        DeleteObject(hBackgroundBitmap);
        for (int i = 0; i < numButton; ++i)
        {
            delete buttons[i];
        }
    }

    void setRunningNewGame(bool runningNewGame)
    {
        this->runningNewGame = runningNewGame;
    }

    bool getRunningNewGame()
    {
		return runningNewGame;
	}

    void Initialize(HWND hwnd)
    {
        // Initialize the window handle
        this->hwnd = hwnd;
        for (int i = 0; i < numButton; ++i)
            createAButton(i);
    }

    void HandleCommand(int id)
    {
        // Handle button/menu item click events based on their ID
        switch (id)
        {
        case 0:
            runningNewGame = true;
            break;
        case 1:
            OnButtonClick("Load Game");
            break;
        case 2:
            OnButtonClick("Settings");
            break;
        case 3:
            OnButtonClick("Credits");
            break;
        case 4:
            OnFileExit();
            break;
        }
    }

    void OnPaint(HDC hdc)
    {
        // Handle painting of the window
        DrawBackgroundWithButtons(hdc);
    }

    // Other member functions for handling window messages can be defined here
};

#endif