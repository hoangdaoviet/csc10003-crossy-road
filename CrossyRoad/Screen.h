#pragma once
#include "Button.h"
#include "HandlerInput.h"

class Screen : public handlerInput{
public:
    void draw(HDC hdc);
    ~Screen() {}
};

Screen *mainScreen;