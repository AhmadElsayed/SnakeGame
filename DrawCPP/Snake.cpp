#include "Snake.h"

///<summary>
/// Generate a new random position for the food and move it to the new position
///</summary>
void Snake::GenerateNewFood()
{
	auto newX = (rand() * 10) % ConsoleHandler::rcWin.right;
	auto newY  = (rand() * 10) % ConsoleHandler::rcWin.bottom;
	foodPoint->ChangePosition(newX, newY);
	
	FoodExists = true;
}

///<summary>
/// Append a new point to the snake body
///</summary>
void Snake::EatFood()
{
	// Make the food point as the same color as snake
	Point p1(foodPoint->posX, foodPoint->posY, SNAKE);
	
	//Add new point to the snake depending on its direction
	switch (Direction)
	{
	case Up:
		Points.push_back(Point(Points.back().posX, Points.back().posY - 10, SNAKE));
		break;
	case Down:
		Points.push_back(Point(Points.back().posX, Points.back().posY + 10, SNAKE));
		break;
	case Right:
		Points.push_back(Point(Points.back().posX + 10, Points.back().posY, SNAKE));
		break;
	case Left:
		Points.push_back(Point(Points.back().posX - 10, Points.back().posY, SNAKE));
		break;
	default:
		break;
	}

	FoodExists = false;
}

///<summary>
/// Check if food doesn't exist generate a new one
/// If not check if the snake is at the same position
///</summary>
void Snake::CheckFood()
{
	if (Moving == 1)
	{
		if (!FoodExists)
		{
			GenerateNewFood();
		}
		else
		{
			// Snake at the food position
			if (foodPoint->posX == Points.back().posX && foodPoint->posY == Points.back().posY)
			{
				EatFood();
			}
		}
	}
}

///<summary>
/// check the interference between the snake points
///</summary>
void Snake::CheckIfHitItSelf()
{
	if (Moving)
		for (int i = 0; i < Points.size() - 1; i++)
		{
			if (Points[i].posX == Points.back().posX && Points[i].posY == Points.back().posY)
			{
				DieHard();
				break;
			}
		}
}

///<summary>
/// Stop the game and show a message about it
///</summary>
void Snake::DieHard()
{
	//TODO: End the game and show any status that it's gone
	for (int i = 0; i < (int)Points.size(); i++)
	{
		//Points[i].Remove();
	}
	Points.clear();
	Moving = false;
	cout << "You Lost";
}

///<summary>
/// Handle the moves of the snake object depending on a specific period
///</summary>
void Snake::StartMoving()
{
	_beginthread(DirectionListenerThread, 0, this);

	while (Moving == 1)
	{
		switch (Direction)
		{
		case Up:
			if (Points.back().posY > 0)
			{
				Points.begin()->Remove();
				Points.erase(Points.begin());
				Points.push_back(Point(Points.back().posX, (Points.back().posY - 10), SNAKE));
			}
			else
				DieHard();
			break;
		case Down:
			if (Points.back().posY < (ConsoleHandler::rcWin.bottom - 10))
			{
				Points.begin()->Remove();
				Points.erase(Points.begin());
				Points.push_back(Point(Points.back().posX, (Points.back().posY + 10), SNAKE));
			}
			else
				DieHard();
			break;
		case Left:
			if (Points.back().posX > ConsoleHandler::rcWin.left)
			{
				Points.begin()->Remove();
				Points.erase(Points.begin());
				Points.push_back(Point(Points.back().posX - 10, Points.back().posY, SNAKE));
			}
			else
				DieHard();
			break;
		case Right:
			if (Points.back().posX < (ConsoleHandler::rcWin.right - 10))
			{
				Points.begin()->Remove();
				Points.erase(Points.begin());
				Points.push_back(Point(Points.back().posX + 10, Points.back().posY, SNAKE));
			}
			else
				DieHard();
			break;
		default:
			continue;
			//cout << endl << "null" << endl;  // not arrow
			break;
		}

		CheckIfHitItSelf();
		CheckFood();
		Sleep(period);
	}
}

///<summary>
/// The function that will keep listening for the arrows click (4 directions)
///</summary>
void Snake::ListenForDirections()
{
	int c = 0;
	while (Moving == 1)
	{
		/* rcWin.left, rcWin.top, rcWin.right, rcWin.bottom */
		switch (c = _getch())
		{
		case Up:
			Direction = Direction != Down ? Up : Down;
			break;
		case Down:
			Direction = Direction != Up ? Down : Up;
			break;
		case Left:
			Direction = Direction != Right ? Left : Right;
			break;
		case Right:
			Direction = Direction != Left ? Right : Left;
			break;
		default:
			continue;
			//cout << endl << "null" << endl;  // not arrow
			break;
		}
	}
}

///<summary>
/// Another thread running and keep listening to directions change
///</summary>
void Snake::DirectionListenerThread(void *p_this)
{
	Snake *myObject = static_cast<Snake *>(p_this);

	myObject->ListenForDirections();
}

///<summary>
/// Default Initializer of the Snake Object
///</summary>
/// <param name="period">Difficulty level</param>
Snake::Snake(int period) : foodPoint(new Point(FOOD))
{
	this -> period = period;

	// Add first two points in snake
	Points.push_back(Point(0, 0, SNAKE));
	Points.push_back(Point(10, 0, SNAKE));
	
	Moving = 1;

	srand(time(0));
}

///<summary>
/// Delete foodpoint pointer and stop snake moving
///</summary>
Snake::~Snake()
{
	Moving = false;
	delete foodPoint;
}
