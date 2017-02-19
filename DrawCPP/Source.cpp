#define _CRT_SECURE_NO_DEPRECATE

#include<windows.h>
#include<iostream>
#include <conio.h>
#include <process.h>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
const COLORREF BCOLOR = RGB(0, 0, 0);
const COLORREF SCOLOR = RGB(135, 206, 235);
const COLORREF FCOLOR = RGB(218, 165, 32);

RECT rcWin;
RECT rcWnd;
//Get a console handle
HWND myconsole;
//Get a handle to device context
HDC mydc;

int Moving = 1, Direction = KEY_RIGHT, FoodPositionX, FoodPositionY;
bool FoodExists = false;


void DrawPoint(int posX, int posY, COLORREF c)
{
	for (double i = posX; i < (posX + 10); i++)
	{
		for (int j = posY; j < (posY + 10); j++)
		{
			SetPixel(mydc, i, j, c);
		}
	}
}

struct Point
{
public:
	int posX;
	int posY;
	COLORREF color;

	Point(int x, int y, COLORREF color)
	{
		posX = x;
		posY = y;
		this->color = color;
		this->Draw();
	}

	void Remove()
	{
		DrawPoint(posX, posY, BCOLOR);
	}

	void Draw()
	{
		DrawPoint(posX, posY, color);
	}

	void ChangePosition(int x, int y)
	{
		this->Remove();
		this->posX = x;
		this->posY = y;
		this->Draw();
	}

	~Point()
	{
		//DrawPoint(posX, posY, BCOLOR);
	}
};

vector<Point> Snake;

void InitData()
{
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
	
	srand(time(0));

	// Add first two points in snake
	Snake.push_back(Point(0, 0, SCOLOR));
	Snake.push_back(Point(10, 0, SCOLOR));

	//TODO: Hide Cursor
	//TODO: Make boundaries for the screen
	//TODO: Show menu for start, and choose dificulty level
	//TODO: Show any indicator if the snake at the food space
	//TODO: Move the code into separated files
}

void ListenForDirections(void *)
{

	int c = 0;
	while (Moving == 1)
	{
		/* rcWin.left, rcWin.top, rcWin.right, rcWin.bottom */
		switch (c = _getch())
		{
		case KEY_UP:
			Direction = Direction != KEY_DOWN ? KEY_UP : KEY_DOWN;
			break;
		case KEY_DOWN:
			Direction = Direction != KEY_UP ? KEY_DOWN : KEY_UP;
			break;
		case KEY_LEFT:
			Direction = Direction != KEY_RIGHT ? KEY_LEFT : KEY_RIGHT;
			break;
		case KEY_RIGHT:
			Direction = Direction != KEY_LEFT ? KEY_RIGHT : KEY_LEFT;
			break;
		default:
			continue;
			//cout << endl << "null" << endl;  // not arrow
			break;
		}
	}

}

void GenerateNewFood()
{
	FoodPositionX = (rand() * 10) % rcWin.right;
	FoodPositionY = (rand() * 10) % rcWin.bottom;

	DrawPoint(FoodPositionX, FoodPositionY, FCOLOR);

	FoodExists = true;
}

// Check if food doesn't exist generate a new one
// If not check if the snake is at the same position
void CheckFood()
{
	if (Moving == 1)
	{
		if (!FoodExists)
		{
			GenerateNewFood();
		}
		else
		{
			if (FoodPositionX == Snake.back().posX && FoodPositionY == Snake.back().posY)
			{
				// Remove existing food point
				DrawPoint(FoodPositionX, FoodPositionY, SCOLOR);
				switch (Direction)
				{
				case KEY_UP:
					Snake.push_back(Point(Snake.back().posX, Snake.back().posY - 10, SCOLOR));
					break;
				case KEY_DOWN:
					Snake.push_back(Point(Snake.back().posX, Snake.back().posY + 10, SCOLOR));
					break;
				case KEY_RIGHT:
					Snake.push_back(Point(Snake.back().posX + 10, Snake.back().posY, SCOLOR));
					break;
				case KEY_LEFT:
					Snake.push_back(Point(Snake.back().posX - 10, Snake.back().posY, SCOLOR));
					break;
				default:
					break;
				}

				FoodExists = false;
			}
		}
	}
}

void DieHard()
{
	//TODO: End the game and show any status that it's gone
	for (int i = 0; i < (int)Snake.size(); i++)
	{
		Snake[i].Remove();
	}
	Snake.clear();
	Moving = false;
	cout << "You Lost";
	getchar();
}

void CheckIfHitItSelf()
{
	for (int i = 0; i < Snake.size() - 1; i++)
	{
		if (Snake[i].posX == Snake.back().posX && Snake[i].posY == Snake.back().posY)
		{
			DieHard();
			break;
		}
	}
}

void StartMoving()
{
	while (Moving == 1)
	{
		switch (Direction)
		{
		case KEY_UP:
			if (Snake.back().posY > 0)
			{
				Snake.begin()->Remove();
				Snake.erase(Snake.begin());
				Snake.push_back(Point(Snake.back().posX, (Snake.back().posY - 10), SCOLOR));
			}
			else
				DieHard();
			break;
		case KEY_DOWN:
			if (Snake.back().posY < (rcWin.bottom - 10))
			{
				Snake.begin()->Remove();
				Snake.erase(Snake.begin());
				Snake.push_back(Point(Snake.back().posX, (Snake.back().posY + 10), SCOLOR));
			}
			else
				DieHard();
			break;
		case KEY_LEFT:
			if (Snake.back().posX > rcWin.left)
			{
				Snake.begin()->Remove();
				Snake.erase(Snake.begin());
				Snake.push_back(Point(Snake.back().posX - 10, Snake.back().posY, SCOLOR));
			}
			else
				DieHard();
			break;
		case KEY_RIGHT:
			if (Snake.back().posX < (rcWin.right - 10))
			{
				Snake.begin()->Remove();
				Snake.erase(Snake.begin());
				Snake.push_back(Point(Snake.back().posX + 10, Snake.back().posY, SCOLOR));
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
		Sleep(70);
	}
}


int main()
{
	system("cls");
	InitData();

	_beginthread(ListenForDirections, 0, NULL);

	StartMoving();

	ReleaseDC(myconsole, mydc);

	return 0;
}