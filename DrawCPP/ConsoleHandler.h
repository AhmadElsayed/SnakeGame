#pragma once
#include <windows.h>

#include <iostream>

using namespace std;

///Singleton class to handle all console events
class ConsoleHandler
{
private:
	static bool instanceFlag;
	static ConsoleHandler *single;

	ConsoleHandler()
	{
		//private constructor
	}
public:
	static RECT rcWin;
	static RECT rcWnd;
	static HWND myconsole;
	static HDC mydc;
	static ConsoleHandler* getInstance();

	static void drawPoint(int posX, int posY, COLORREF c);

	~ConsoleHandler()
	{
		instanceFlag = false;
	}
};
//
//namespace ConsoleHandler{
//	static RECT rcWin;
//	static RECT rcWnd;
//	static HWND myconsole;
//	static HDC mydc;
//
//	void InitConsoleHandler();
//	void DrawPoint(int posX, int posY, COLORREF c);
//};

