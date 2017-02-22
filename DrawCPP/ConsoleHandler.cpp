#include "ConsoleHandler.h"

/// <summary>
/// Flag to define whether the single instance has created or not yet.
/// </summary>
bool ConsoleHandler::instanceFlag = false;

/// <summary>
/// The singleton object that will be initialized once and used every time.
/// </summary>
ConsoleHandler* ConsoleHandler::single = NULL;

RECT ConsoleHandler::rcWin;
RECT ConsoleHandler::rcWnd;
HWND ConsoleHandler::myconsole;
HDC ConsoleHandler::mydc;

/// <summary>
/// Color definition foreach point Type
/// </summary>
map<PointType, COLORREF> ConsoleHandler::PointColor =
{
	{ SNAKE, RGB(135, 206, 235) },
	{ BACKGROUND, RGB(0, 0, 0) },
	{ FOOD, RGB(218, 165, 32) }
};

/// <summary>
/// Function will be called everytime creating a console object
/// </summary>
/// <returns>The static console handler pointer</returns>
ConsoleHandler* ConsoleHandler::getInstance()
{
	if (!instanceFlag)
	{
		single = new ConsoleHandler();
		//////////////////////////////
		myconsole = GetConsoleWindow();
		mydc = GetDC(myconsole);
		HWND parWnd = GetParent(myconsole); // Get the parent window.
		HDC parDc = GetDC(parWnd); // Get its DC.

		GetWindowRect(myconsole, &rcWnd);

		GetClipBox(mydc, &rcWin);
		// Copy from parent DC.
		BitBlt(mydc, rcWin.left, rcWin.top, rcWin.right - rcWin.left,
			rcWin.bottom - rcWin.top, parDc, rcWnd.left, rcWnd.top, 0);

		ReleaseDC(parWnd, parDc);
		//////////////////////////////
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

/// <summary>
/// Draw point function depending on its coordinates and type
/// </summary>
/// <param name="posX">X coordinate of the point</param>
/// <param name="posY">Y coordinate of the point</param>
/// <param name="type">Point Type</param>
void ConsoleHandler::drawPoint(int posX, int posY, PointType type)
{
	for (double i = posX; i < (posX + 10); i++)
	{
		for (int j = posY; j < (posY + 10); j++)
		{
			SetPixel(mydc, i, j, PointColor[type]);
		}
	}
}