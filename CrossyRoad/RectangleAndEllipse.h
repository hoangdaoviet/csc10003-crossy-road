#pragma once
#include "Shape.h"

class RectangleShape : public Shape {
public:
    void Draw(HDC hdc, int x, int y, int width, int height) const override {
        // Draw a rectangle
    }
};
