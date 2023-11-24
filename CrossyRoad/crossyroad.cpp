#include "Button.h"
#include "handlerInput.h"
#include "Screen.h"
#include "menuScreen.h"
#include "Shape.h"
#include "RectangleAndEllipse.h"
#include "readBitmap.h"
#include <windows.h>

HBITMAP hBackgroundBitmap; // Bitmap for the background image
Button *buttons[5]; // Array of buttons
readBitmapForImage a;

void OnButtonClick(HWND hwnd, const char *buttonName)
{
    std::ostringstream message;
    message << buttonName << "";
    MessageBox(hwnd, message.str().c_str(), "", MB_OK);
}

// Function to handle menu item click event
void OnFileExit(HWND hwnd)
{
    if (MessageBox(hwnd, "Do you want to exit game ?", "", MB_OKCANCEL) == IDOK)
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    else
        return;
}

// Function to set button image
void setButtonImage()
{
    buttons[0] = new Button(new RectangleShapes(), a.LoadBitmapButton1());
    buttons[1] = new Button(new RectangleShapes(), a.LoadBitmapButton2());
    buttons[2] = new Button(new RectangleShapes(), a.LoadBitmapButton3());
    buttons[3] = new Button(new RectangleShapes(), a.LoadBitmapButton4());
    buttons[4] = new Button(new RectangleShapes(), a.LoadBitmapButton5());
}

void createAButton(HWND hwnd, int i)
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
        MessageBox(NULL, "Button Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    menuScreen menuScreen;
    readBitmapForImage read;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        hBackgroundBitmap = read.LoadBitmapBackGround();
        // i want to create a button that place on the  buttons

        setButtonImage();
        for (int i = 0; i < 5; ++i)
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
        menuScreen.draw(hdc, hwnd, hBackgroundBitmap);
        // createAButton(hwnd);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        // Release resources
        DeleteObject(hBackgroundBitmap);

        // Delete buttons
        for (int i = 0; i < 5; ++i) // Adjust the loop range based on the number of buttons
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