#include <windows.h>
#include "GameMenu.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static GameMenu *gameMenu;

    switch (uMsg)
    {
    case WM_CREATE:
    {
        gameMenu = new GameMenu();
        gameMenu->Initialize(hwnd);
        break;
    }
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        gameMenu->HandleCommand(id);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        gameMenu->OnPaint(hdc);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        delete gameMenu; // Cleanup when the window is destroyed
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = "GameMenuWindowClass";
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&windowClass);

    // Create the window
    HWND hwnd = CreateWindow(
        "GameMenuWindowClass", "CROSSY ROAD GAME",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL
    );

    // Show the window and run the message loop
    ShowWindow(hwnd, nCmdShow);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}