#include "Shape.h"

class Button {
private:
    int width;
    int height;
    Shape* shape;
    HBITMAP image;
    bool isPress(int x, int y, int width, int height) const {
        return (x >= 0 && x <= width && y >= 0 && y <= height);
    }
    
public:
    Button(Shape* shape, HBITMAP image) : shape(shape), image(image) {
        BITMAP bm;
        GetObject(image, sizeof(bm), &bm);
        width = bm.bmWidth;
        height = bm.bmHeight;
    }

    int getWidth() const {
        return width;
    }
    
    int getHeight() const {
        return height;
    }
    
    void Draw(HDC hdc, int x, int y, int width, int height) const {
        // Draw the shape
        //shape->Draw(hdc, x, y, width, height);

        // Draw the image on top of the shape
        if (image != nullptr) {
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMem, image);
            BitBlt(hdc, x, y, width, height, hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem, hBitmapOld);
            DeleteDC(hdcMem);
        }
    }

    HBITMAP GetImage() const {
        return image;
    }
    
    ~Button() {
        delete shape;
        DeleteObject(image);
    }

    bool isButtonPressed(const Button& button, int x, int y, int width, int height) {
        return button.isPress(x, y, width, height);
    }
};
