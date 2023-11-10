#include <windows.h>
#include <sstream>

// Function to handle button click event
void OnButtonClick(HWND hwnd, const char* buttonName) {
    std::ostringstream message;
    message << buttonName << " Clicked!";
    MessageBox(hwnd, message.str().c_str(), "Button Click Event", MB_OK);
}

// Function to handle menu item click event
void OnFileExit(HWND hwnd) {
    MessageBox(hwnd, "Exiting Game...", "Menu Item Click Event", MB_OK);
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}

// Function to center the buttons near the bottom of the window
void CenterButtons(HWND hwnd) {
    RECT rect;
    GetClientRect(hwnd, &rect);

    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    int buttonWidth = 150;
    int buttonHeight = 30;
    int buttonSpacing = 10;

    // Calculate the total height occupied by buttons
    int totalButtonHeight = 6 * buttonHeight + 5 * buttonSpacing;

    // Center the buttons horizontally
    int xPosition = (windowWidth - buttonWidth) / 2;

    // Center the buttons vertically
    int yPosition = (windowHeight - totalButtonHeight) / 2;

    // Set the position for each button
    for (int i = 1; i <= 6; ++i) {
        HWND button = GetDlgItem(hwnd, i);
        SetWindowPos(button, NULL, xPosition, yPosition, buttonWidth, buttonHeight, SWP_NOZORDER);
        yPosition += buttonHeight + buttonSpacing;
    }
}

// Window procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Create buttons in the specified order
            const char* buttonNames[] = {"Start Game", "File Save", "Achievements", "Options", "Credits", "Exit"};
            for (int i = 0; i < 6; ++i) {
                CreateWindow(
                    "BUTTON", buttonNames[i], WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                    0, 0, 150, 30, hwnd, (HMENU)(i + 1), NULL, NULL
                );
            }

            // Center the buttons within the window
            CenterButtons(hwnd);
            break;
        }
        case WM_COMMAND: {
            // Handle button click
            switch (LOWORD(wParam)) {
                case 1:
                    OnButtonClick(hwnd, "Start Game");
                    break;
                case 2:
                    OnButtonClick(hwnd, "File Save");
                    break;
                case 3:
                    OnButtonClick(hwnd, "Achievements");
                    break;
                case 4:
                    OnButtonClick(hwnd, "Options");
                    break;
                case 5:
                    OnButtonClick(hwnd, "Credits");
                    break;
                case 6:
                    OnFileExit(hwnd);
                    break;
            }
            break;
        }
        case WM_SIZE: {
            // Re-center the buttons when the window is resized
            CenterButtons(hwnd);
            break;
        }
        case WM_DESTROY: {
            // Post quit message when the window is destroyed
            PostQuitMessage(0);
            break;
        }
        default: {
            // Call the default window procedure for other messages
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    return 0;
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = "GameMenuWindowClass";
    RegisterClass(&windowClass);

    // Create the window with a fixed size (1920x1080)
    HWND hwnd = CreateWindow(
        "GameMenuWindowClass",  // Window class
        "Game Menu Example",    // Window title
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,  // Window style (fixed size)
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 675,  // Window position and size
        NULL, NULL, hInstance, NULL  // Parent window, menu, instance, and creation data
    );

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
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
