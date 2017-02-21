#pragma once
#include <windows.h>
#include "ConsoleHandler.h"

class Point
{
public:
	Point();
	Point(int x, int y, COLORREF c);
	
	int posX;
	int posY;
	COLORREF color;

	void Remove();
	void Draw();
	void ChangePosition(int x, int y);

	~Point();
};

