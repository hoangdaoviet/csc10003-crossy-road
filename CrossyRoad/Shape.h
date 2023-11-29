#pragma once
#include <windows.h>
#include <sstream>
#include <string>

class Shape {
public:
    virtual void Draw(HDC hdc, int x, int y, int width, int height) const = 0;
    virtual ~Shape() {}
};