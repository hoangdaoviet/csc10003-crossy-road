#include "GameCredits.h"

HBITMAP GameCredits::LoadBitmapImage(const wchar_t* filename)
{
    return (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void GameCredits::setButtonImage()
{
    buttons = new Button(new RectangleShape(), LoadBitmapImage(L"RETURNBUTTON.bmp"));
    // Add more buttons with different shapes as needed
}

void GameCredits::createButton()
{
    int xPosition = 1000;
    int yPosition = 500;

    // Load the image
    HBITMAP buttonImage = buttons->GetImage();
    int buttonWidth = buttons->getWidth();
    int buttonHeight = buttons->getHeight();
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
        (HMENU)1,                          // No menu.
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

void GameCredits::DrawBackgroundWithButtons(HDC hdc)
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

GameCredits::GameCredits()
{
    hBackgroundBitmap = LoadBitmapImage(L"CREDITSMENU.bmp");
    setButtonImage();
}

GameCredits::~GameCredits()
{
    // Release resources, delete buttons, and perform cleanup
    DeleteObject(hBackgroundBitmap);
    delete buttons;
  
}

void GameCredits::Initialize(HWND hwnd)
{
    this->hwnd = hwnd;
    createButton();
}

void GameCredits::OnPaint(HDC hdc, HWND hwnd) {
    DrawBackgroundWithButtons(hdc);
}

void GameCredits::HandleCommand(int id) {
    if (id == 0) {
        isRunning = false;
        //openMainMenu();
    }
}
void RunCreditsLoop(HDC hdc, GameCredits *a) {
    a->isRunning = true;
    a->DrawBackgroundWithButtons(hdc);
    while (a->isRunning) 
    {
        MSG message;

        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
	}
}

void GameCredits::openMainMenu()
{
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}