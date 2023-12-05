#include "GameMenu.h"

HBITMAP GameMenu::LoadBitmapImage(const wchar_t* filename)
{
    return (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void GameMenu::setButtonImage()
{
    buttons[0] = new Button(new RectangleShape(), LoadBitmapImage(L"NEWGAME.bmp"));
    buttons[1] = new Button(new RectangleShape(), LoadBitmapImage(L"LOADGAME.bmp"));
    buttons[2] = new Button(new RectangleShape(), LoadBitmapImage(L"SETTINGS.bmp"));
    buttons[3] = new Button(new RectangleShape(), LoadBitmapImage(L"CREDITS.bmp"));
    buttons[4] = new Button(new RectangleShape(), LoadBitmapImage(L"EXIT.bmp"));
    // Add more buttons with different shapes as needed
}

void GameMenu::createAButton(int i)
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

void GameMenu::OnButtonClick(const char* buttonName)
{
    // Handle button click event
    std::ostringstream message;
    message << buttonName << "";
    MessageBox(hwnd, L"", L"", MB_OK);
}

void GameMenu::OnFileExit()
{
    // Handle file exit event
    if (MessageBox(hwnd, L"Do you want to exit game ?", L"", MB_OKCANCEL) == IDOK)
        PostMessage(hwnd, WM_CLOSE, 0, 0);
}

void GameMenu::DrawBackgroundWithButtons(HDC hdc)
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

GameMenu::GameMenu()
{
    // Initialize variables and load resources
    hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 255));
    hBackgroundBitmap = LoadBitmapImage(L"crossyroad.bmp");
    setButtonImage();
    // Initialize other variables or perform additional setup if needed
}

GameMenu::~GameMenu()
{
    // Release resources, delete buttons, and perform cleanup
    DeleteObject(hBackgroundBrush);
    DeleteObject(hBackgroundBitmap);
    for (int i = 0; i < numButton; ++i)
    {
        delete buttons[i];
    }
}

void GameMenu::setRunningNewGame(bool runningNewGame)
{
    this->runningNewGame = runningNewGame;
}

void GameMenu::setRunningLoadGame(bool runningLoadGame)
{
    this->runningLoadGame = runningLoadGame;
}

void GameMenu::setRunningSettings(bool runningSettings)
{
    this->runningSettings = runningSettings;
}

void GameMenu::setRunningCredits(bool runningCredits)
{
    this->runningCredits = runningCredits;
}

bool GameMenu::getRunningNewGame()
{
    return runningNewGame;
}

bool GameMenu::getRunningLoadGame()
{
    return runningLoadGame;
}

bool GameMenu::getRunningSettings()
{
    return runningSettings;
}

bool GameMenu::getRunningCredits()
{
    return runningCredits;
}

void GameMenu::Initialize(HWND hwnd)
{
    this->hwnd = hwnd;
    // Initialize the window handle
    
    for (int i = 0; i < numButton; ++i)
        createAButton(i);
}

void GameMenu::HandleCommand(int id)
{
    // Handle button/menu item click events based on their ID
    switch (id)
    {
    case 0:
        runningNewGame = true;
        break;
    case 1:
        runningLoadGame = true;
        break;
    case 2:
        runningSettings = true;
        break;
    case 3:
        runningCredits = true;
        break;
    case 4:
        OnFileExit();
        break;
    }
}

void GameMenu::OnPaint(HDC hdc, HWND hwnd)
{
    // Handle painting of the window
    DrawBackgroundWithButtons(hdc);
   // Initialize(hwnd);
}
