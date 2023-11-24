#pragma once
#include "Screen.h"
#include <windows.h>
#include <sstream>
#include <string>
#include "Shape.h"
#include "Button.h"
#include "RectangleAndEllipse.h"
#include <iostream>

class menuScreen : public Screen{
public:
    menuScreen();
    void draw(HDC hdc, HWND hwnd, HBITMAP hBackgroundBitmap) override;
    ~menuScreen();
};