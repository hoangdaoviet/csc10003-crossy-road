#pragma once
#include "Button.h"
#include "HandlerInput.h"

class Screen : public handlerInput{
public:
    Screen(){};
    virtual void draw(HDC hdc, HWND hwnd, HBITMAP hBackgroundBitmap) = 0;
    ~Screen() {}
};

