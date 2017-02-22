#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "Point.h"
#include "Shared.h"
#include <conio.h>
#include <process.h>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

class Snake
{
public:
	///<summary>
	/// Default Initializer of the Snake Object
	///</summary>
	/// <param name="period">Difficulty level</param>
	Snake(int period = 100);

	///<summary>
	/// The function that will keep listening for the arrows click (4 directions)
	///</summary>
	void ListenForDirections();

	///<summary>
	/// Handle the moves of the snake object depending on a specific period
	///</summary>
	void StartMoving();

	///<summary>
	/// Delete foodpoint pointer and stop snake moving
	///</summary>
	~Snake();

private:
	///<summary>
	/// A flag to check that the snake is still alive and moving
	///</summary>
	int Moving;

	///<summary>
	/// The snake set of points that grow up every time he eat his food 
	///</summary>
	vector<Point> Points;

	///<summary>
	/// The current direction of the snake (by default right)
	///</summary>
	DIRECTION Direction = Right;

	///<summary>
	/// The game level of the speed of the snake depends on this period between moves
	///</summary>
	int period;

	///<summary>
	/// Pointer to the food point that changes its position each time after the snake eat it
	///</summary>
	Point *foodPoint;

	///<summary>
	/// A flag to check if there's already a food or i have to generate a new one
	///</summary>
	bool FoodExists = false;

	///<summary>
	/// Another thread running and keep listening to directions change
	///</summary>
	static void DirectionListenerThread(void *);

	///<summary>
	/// Generate a new random position for the food and move it to the new position
	///</summary>
	void GenerateNewFood();
	
	///<summary>
	/// Check if food doesn't exist generate a new one
	/// If not check if the snake is at the same position
	///</summary>
	void CheckFood();

	///<summary>
	/// Append a new point to the snake body
	///</summary>
	void EatFood();

	///<summary>
	/// check the interference between the snake points
	///</summary>
	void CheckIfHitItSelf();

	///<summary>
	/// Stop the game and show a message about it
	///</summary>
	void DieHard();
};

