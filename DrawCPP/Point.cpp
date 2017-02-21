#include "Point.h"
#include "ConsoleHandler.h"

Point::Point()
{
}

Point::Point(int x, int y, COLORREF c)
{
	posX = x;
	posY = y;
	color = RGB(135, 206, 235);
	this->Draw();
}

void Point::Remove()
{
	ConsoleHandler::getInstance()->drawPoint(posX, posY, RGB(0, 0, 0));
}

void Point::Draw()
{
	ConsoleHandler::getInstance()->drawPoint(posX, posY, color);
}

void Point::ChangePosition(int x, int y)
{
	this->Remove();
	this->posX = x;
	this->posY = y;
	this->Draw();
}

Point::~Point()
{
}
