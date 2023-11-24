#include "menuScreen.h"
#include "readBitmap.h"

menuScreen::menuScreen()
{
}

menuScreen::~menuScreen()
{
}

// Function to draw the background with an image
void menuScreen::draw(HDC hdc, HWND hwnd, HBITMAP hBackgroundBitmap)
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



