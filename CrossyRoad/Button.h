#pragma once
#include "Shape.h"

class Button{
private:
    int width;
    int height;
    Shape *shape;
    HBITMAP image;
    bool isPress(int x, int y, int width, int height) const{
        return (x >= 0 && x <= width && y >= 0 && y <= height);
    }

public:
    Button(Shape *shape, HBITMAP image) : shape(shape), image(image){
        BITMAP bm;
        GetObject(image, sizeof(bm), &bm);
        width = bm.bmWidth;
        height = bm.bmHeight;
    }

    int getWidth() const;

    int getHeight() const;

    void Draw(HDC hdc, int x, int y, int width, int height) const;

    HBITMAP GetImage() const;

    ~Button();

    bool isButtonPressed(const Button &button, int x, int y, int width, int height);
};

class buttonList{
    private:
        Button *buttons;
        int numButtons;
    public:
        buttonList(Button *buttons, int numButtons) : buttons(buttons), numButtons(numButtons){}

        Button *getButtons() const{
            return buttons;
        }

        int getNumButtons() const{
            return numButtons;
        }

        ~buttonList(){
            delete[] buttons;
        }
};
