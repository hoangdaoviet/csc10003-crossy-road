#include <windows.h>
#include <sstream>
#include <string>
#include "Shape.h"
#include "Button.h"
#include "RectangleAndEllipse.h"
#include <iostream>
#define numButton 5
HBRUSH hBackgroundBrush;   // Brush for the background color
HBITMAP hBackgroundBitmap; // Bitmap for the background image

Button *buttons[5]; // Array of buttons

// Function to load a bitmap image for the background
HBITMAP LoadBitmapImage()
{
    return (HBITMAP)LoadImage(NULL, "crossyroad.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP LoadBitmapButton1()
{
    return (HBITMAP)LoadImage(NULL, "NEWGAME.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP LoadBitmapButton2()
{
    return (HBITMAP)LoadImage(NULL, "LOADGAME.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP LoadBitmapButton3()
{
    return (HBITMAP)LoadImage(NULL, "SETTINGS.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP LoadBitmapButton4()
{
    return (HBITMAP)LoadImage(NULL, "CREDITS.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP LoadBitmapButton5()
{
    return (HBITMAP)LoadImage(NULL, "EXIT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void setButtonImage()
{
    buttons[0] = new Button(new RectangleShape(), LoadBitmapButton1());
    buttons[1] = new Button(new RectangleShape(), LoadBitmapButton2());
    buttons[2] = new Button(new RectangleShape(), LoadBitmapButton3());
    buttons[3] = new Button(new RectangleShape(), LoadBitmapButton4());
    buttons[4] = new Button(new RectangleShape(), LoadBitmapButton5());
    // Add more buttons with different shapes as needed
}

// Function to handle button click event
void OnButtonClick(HWND hwnd, const char *buttonName)
{
    std::ostringstream message;
    message << buttonName << "";
    MessageBox(hwnd, message.str().c_str(), "", MB_OK);
}

// Function to handle menu item click event
void OnFileExit(HWND hwnd)
{
    if(MessageBox(hwnd, "Do you want to exit game ?", "", MB_OKCANCEL) == IDOK)
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    else 
        return;
}

// Function to draw the background with an image
void DrawBackgroundWithButtons(HWND hwnd, HDC hdc)
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
void createAButton(HWND hwnd,int i)
{

    int xPosition = 200;
    int yPosition = 250 + i * 80;


    // Load the image
    HBITMAP buttonImage = buttons[i]->GetImage();
    int buttonWidth = buttons[i]->getWidth();
    int buttonHeight = buttons[i]->getHeight();
    if (buttonImage == NULL)
    {
        MessageBox(NULL, "Image Loading Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    HWND hButton = CreateWindow(
        "BUTTON",                          // Button control
        "button",                          // No text for the button
        WS_VISIBLE | WS_CHILD | BS_BITMAP, // Styles
        xPosition,                         // x position
        yPosition,                         // y position
        buttonWidth,                       // Button width
        buttonHeight,                      // Button height
        hwnd,                              // Parent window
        (HMENU) i,                              // No menu.
        NULL,
        NULL); // No additional data.

    if (hButton)
    {
        // Set the button's image
        SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)buttonImage);
    }
    else
    {
        MessageBox(NULL, "Button Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
}
// Window procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        hBackgroundBitmap = LoadBitmapImage();
        // i want to create a button that place on the  buttons

        setButtonImage();
        for (int i = 0; i < numButton; ++i)
            createAButton(hwnd, i);

        break;
    }
    case WM_COMMAND:
    {
        // Handle menu item selection
        if (HIWORD(wParam) == 0)
        {
            switch (LOWORD(wParam))
            {
            case 0:
                OnButtonClick(hwnd, "New Game");
                break;
            case 1:
                OnButtonClick(hwnd, "Load Game");
                break;
            case 2:
                OnButtonClick(hwnd, "Settings");
                break;
            case 3:
                OnButtonClick(hwnd, "Credits");
                break;
            case 4:
                OnFileExit(hwnd);
                break;
            }
        }
        break;
    }
    case WM_SIZE:
    {

        break;
    }
    case WM_ERASEBKGND:
    {
        return 1;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Draw the background with an image
        DrawBackgroundWithButtons(hwnd, hdc);
        // createAButton(hwnd);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        // Release resources
        DeleteObject(hBackgroundBrush);
        DeleteObject(hBackgroundBitmap);

        // Delete buttons
        for (int i = 0; i < numButton; ++i) // Adjust the loop range based on the number of buttons
        {
            delete buttons[i];
        }

        // Post quit message when the window is destroyed
        PostQuitMessage(0);
        break;
    }
    default:
    {
        // Call the default window procedure for other messages
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    }

    return 0;
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class
    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = "GameMenuWindowClass";
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Set a default background color
    RegisterClass(&windowClass);

    // Create the window with a fixed size (1920x1080)
    HWND hwnd = CreateWindow(
        "GameMenuWindowClass",                   // Window class
        "CROSSY ROAD GAME",                      // Window title
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, // Window style (fixed size)
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, // Window position and size
        NULL, NULL, hInstance, NULL              // Parent window, menu, instance, and creation data
    );
    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Center the window on the screen
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;
    SetWindowPos(hwnd, HWND_TOP, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, 0, 0, SWP_NOSIZE);

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
