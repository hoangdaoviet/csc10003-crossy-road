#include "readBitmap.h"

HBITMAP readBitmapForImage::LoadBitmapBackGround(){
    return (HBITMAP)LoadImage(NULL, "crossyroad.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP readBitmapForImage::LoadBitmapButton1(){
    return (HBITMAP)LoadImage(NULL, "NEWGAME.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP readBitmapForImage::LoadBitmapButton2(){
    return (HBITMAP)LoadImage(NULL, "LOADGAME.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP readBitmapForImage::LoadBitmapButton3(){
    return (HBITMAP)LoadImage(NULL, "SETTINGS.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP readBitmapForImage::LoadBitmapButton4(){
    return (HBITMAP)LoadImage(NULL, "CREDITS.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP readBitmapForImage::LoadBitmapButton5(){
    return (HBITMAP)LoadImage(NULL, "EXIT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}