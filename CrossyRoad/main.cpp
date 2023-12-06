#include "Map.h"
#include "Sprite.h"
#include "player.h"
#include "GameMenu.h"
#include "SimulateGame.h"
#include "GameCredits.h"
#include "GameSettings.h"

using namespace std;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    static GameMenu* gameMenu;
    static GameCredits* gameCredits;
    switch (uMsg)
    {
        case WM_CREATE:
        {
            gameMenu = new GameMenu();
            gameMenu->Initialize(hwnd);
            gameCredits = new GameCredits();
            break;
        }
        case WM_COMMAND:
        {
            int id = LOWORD(wParam);
            gameMenu->HandleCommand(id);
            if (gameMenu->getRunningNewGame())
            {
                RunGameLoop(GetDC(hwnd));
                gameMenu->setRunningNewGame(false);

                // Optionally, reinitialize the GameMenu after the game loop.
                delete gameMenu;
                gameMenu = new GameMenu();
                gameMenu->setRunningNewGame(false);
                gameMenu->Initialize(hwnd);

                // Additionally, repaint the window if needed.
                InvalidateRect(hwnd, NULL, TRUE);
            }
            else if (gameMenu->getRunningCredits())
            {
                //RunCreditsLoop(GetDC(hwnd), gameCredits, hwnd);
                //gameMenu->setRunningCredits(false);

                //// Optionally, reinitialize the GameMenu after the game loop.
                //delete gameMenu;
                //gameMenu = new GameMenu();
                //gameMenu->setRunningCredits(false);
                //gameMenu->Initialize(hwnd);
            
                //// Additionally, repaint the window if needed.
                //InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            gameMenu->OnPaint(hdc, hwnd);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_CLOSE:
        case WM_DESTROY:
        {
            delete gameMenu;
            PostQuitMessage(0);
            running = false;
            break;
        }
        case WM_SIZE: {
            RECT rect;
            GetClientRect(hwnd, &rect);
            render_state.width = rect.right - rect.left;
            render_state.height = rect.bottom - rect.top;

            int size = render_state.height * render_state.width * sizeof(unsigned int);

            if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
            render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
            render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
            render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
            render_state.bitmap_info.bmiHeader.biPlanes = 1;
            render_state.bitmap_info.bmiHeader.biBitCount = 32;
            render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
        } break; 
            
        default: {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Create window class
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpszClassName = L"Nhom 2 OOP Crossy Road";
    window_class.lpfnWndProc = window_callback;

    // Create Register class
    RegisterClass(&window_class);

    // Create window
    // WS_THICKFRAME IS USED FOR RESIZING WINDOW
    // WS_MAXIMIZEBOX IS USED FOR MAXIMIZING THE WINDOW
    HWND window = CreateWindow(window_class.lpszClassName, L"Crossy Road!", (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX) | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1296, 759, 0, 0, hInstance, 0);
    HDC hdc = GetDC(window);
    generateMap();

    while (running)
    {   
        // Input
        ShowWindow(window, nCmdShow);
        MSG message;

        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return 1;
}