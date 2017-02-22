#pragma once
#include <windows.h>
#include "Shared.h"
#include <iostream>
#include <map>

using namespace std;

/// <summary>
/// Singleton class to handle all console events
/// </summary>
class ConsoleHandler
{
private:
	/// <summary>
	/// Flag to define whether the single instance has created or not yet.
	/// </summary>
	static bool instanceFlag;

	static RECT rcWnd;
	static HWND myconsole;
	static HDC mydc;

	/// <summary>
	/// The singleton object that will be initialized once and used every time.
	/// </summary>
	static ConsoleHandler *single;

	/// <summary>
	/// Color definition foreach point Type
	/// </summary>
	static map<PointType, COLORREF> PointColor;

	ConsoleHandler()
	{
		//private constructor
	}
public:
	/// <summary>
	/// Function will be called everytime creating a console object
	/// </summary>
	/// <returns>The static console handler pointer</returns>
	static ConsoleHandler* getInstance();

	static RECT rcWin;

	/// <summary>
	/// Draw point function depending on its coordinates and type
	/// </summary>
	/// <param name="posX">X coordinate of the point</param>
	/// <param name="posY">Y coordinate of the point</param>
	/// <param name="type">Point Type</param>
	static void drawPoint(int posX, int posY, PointType type);

	/// <summary>
	/// Class destructor
	/// </summary>
	~ConsoleHandler()
	{
		instanceFlag = false;
	}
};

