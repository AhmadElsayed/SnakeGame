#include "Point.h"
#include "ConsoleHandler.h"

/// <summary>
/// Add new point with type without drawing 
/// </summary>
/// <param name="type">Point Type</param>
Point::Point(PointType type)
{
	this->type = type;
}

/// <summary>
/// The public constructor that assign the point 
/// </summary>
/// <param name="posX">X coordinate of the point</param>
/// <param name="posY">Y coordinate of the point</param>
/// <param name="type">Point Type</param>
Point::Point(int x, int y, PointType type)
{
	posX = x;
	posY = y;
	this->type = type;
	console = ConsoleHandler::getInstance();
	this->Draw();
}

/// <summary>
/// Call the draw function in the console depending on the X, Y and background type
/// </summary>
void Point::Remove()
{
	console->drawPoint(posX, posY, BACKGROUND);
}

/// <summary>
/// Call the draw function in the console depending on the X, Y and point Type
/// </summary>
void Point::Draw()
{
	console->drawPoint(posX, posY, type);
}

/// <summary>
/// Call the remove function
/// Call the draw function with new coordinates
/// </summary>
void Point::ChangePosition(int x, int y)
{
	this->posX = x;
	this->posY = y;
	this->Draw();
}

/// <summary>
/// Call the remove function
/// Call the draw function with new point type
/// </summary>
void Point::ChangeType(PointType type)
{
	this->Remove();
	this->type = type;
	this->Draw();
}