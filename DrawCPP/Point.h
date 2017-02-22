#pragma once
#include <windows.h>
#include "ConsoleHandler.h"

/// <summary>
/// The class is responsible for drawing and removing the point with its location X, Y
/// </summary>
class Point
{
public:
	/// <summary>
	/// Add new point with type without drawing 
	/// </summary>
	/// <param name="type">Point Type</param>
	Point(PointType type);

	/// <summary>
	/// The public constructor that assign the point 
	/// </summary>
	/// <param name="posX">X coordinate of the point</param>
	/// <param name="posY">Y coordinate of the point</param>
	/// <param name="type">Point Type</param>
	Point(int posX, int posY, PointType type);

	/// <summary>
	/// X coordinate of the point
	/// </summary>
	int posX;

	/// <summary>
	/// Y coordinate of the point
	/// </summary>
	int posY;

	/// <summary>
	/// Call the draw function in the console depending on the X, Y and background type
	/// </summary>
	void Remove();
	
	/// <summary>
	/// Call the draw function in the console depending on the X, Y and point Type
	/// </summary>
	void Draw();
	
	/// <summary>
	/// Call the remove function
	/// Call the draw function with new coordinates
	/// </summary>
	void ChangePosition(int x, int y);

	/// <summary>
	/// Call the remove function
	/// Call the draw function with new point type
	/// </summary>
	void ChangeType(PointType type);

	~Point() {
		// Destructor
	}

private:

	/// <summary>
	/// Type of the Point (Snake, Background, Food)
	/// </summary>
	PointType type;

	/// <summary>
	/// Object of Console Handler that will be used to draw and remove point
	/// </summary>
	ConsoleHandler *console;
};

