#include "Button.h"

int Button::getWidth() const{
    return width;
}

int Button::getHeight() const{
    return height;
}

void Button::Draw(HDC hdc, int x, int y, int width, int height) const{
    // Draw the image on top of the shape
    if (image != nullptr)
    {
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMem, image);
        BitBlt(hdc, x, y, width, height, hdcMem, 0, 0, SRCCOPY);
        SelectObject(hdcMem, hBitmapOld);
        DeleteDC(hdcMem);
    }
}

HBITMAP Button::GetImage() const{
    return image;
}

Button::~Button(){
    delete shape;
    DeleteObject(image);
}

bool Button::isButtonPressed(const Button &button, int x, int y, int width, int height){
    return button.isPress(x, y, width, height);
}

