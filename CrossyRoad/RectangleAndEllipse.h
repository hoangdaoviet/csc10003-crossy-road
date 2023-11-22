#include "Shape.h"

class RectangleShape : public Shape {
public:
    void Draw(HDC hdc, int x, int y, int width, int height) const override {
        // Draw a rectangle
        Rectangle(hdc, x, y, x + width, y + height);
    }

    /*bool isButtonPressed(int x, int y, int width, int height) const override{
        return (x >= 0 && x <= width && y >= 0 && y <= height);
    }*/
};
