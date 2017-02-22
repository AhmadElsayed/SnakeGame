#include<iostream>
#include "Snake.h"

using namespace std;

//TODO: Hide Cursor
//TODO: Make boundaries for the screen
//TODO: Show menu for start, and choose dificulty level
//TODO: Show any indicator if the snake at the food space
//TODO: Move the code into separated files

int main()
{
	system("cls");

	Snake SnakeObj = Snake(100);

	SnakeObj.StartMoving();

	return 0;
}