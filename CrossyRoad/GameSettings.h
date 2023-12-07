#pragma once
#include "GameMenu.h"
#include "RectangleAndEllipse.h"
#include "Button.h"
#include "iostream"
#include "string"
#include "windows.h"

class GameSettings
{
	private:
		static constexpr int numButton = 2;
		HBITMAP hBackgroundBitmap;  // Bitmap for the background image
		HWND hwnd;                  // Window handle
		Button* buttons[numButton];
		bool runningSettingsScreen = false;
		

		//private functions
		static HBITMAP LoadBitmapImage(const wchar_t* filename);
		void setButtonImage();
		void createAButton(int i);
		void drawBackgroundWithButtons(HDC hdc);

	public:
		GameSettings();
		~GameSettings();
		void setRunningCreditsScreen(bool runningCreditsScreen);
		bool getRunningCreditsScreen();
		void Initialize(HWND hwnd);
		void HandleCommand(int id);
		void OnPaint(HDC hdc, HWND hwnd);
};


