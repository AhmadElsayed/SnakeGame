#include "ConsoleHandler.h"

bool ConsoleHandler::instanceFlag = false;
ConsoleHandler* ConsoleHandler::single = NULL;

RECT ConsoleHandler::rcWin;
RECT ConsoleHandler::rcWnd;
HWND ConsoleHandler::myconsole;
HDC ConsoleHandler::mydc;

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

void ConsoleHandler::drawPoint(int posX, int posY, COLORREF c)
{
	for (double i = posX; i < (posX + 10); i++)
	{
		for (int j = posY; j < (posY + 10); j++)
		{
			SetPixel(mydc, i, j, c);
		}
	}
}