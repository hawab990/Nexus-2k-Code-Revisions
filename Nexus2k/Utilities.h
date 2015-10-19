#pragma once
#include "Board.h"
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Threading;

ref class Utilities
{
	public: property Point^ pickedCell;
private:
	
	Board^ gameBoard;


public:
	Utilities(Board^ gameBoard);
	int detectFive();
	void drawPossibleMoves(Graphics^ graphics);
	List<Point>^ findMovementPath(Point^ endPoint);
	//Takes one point and moves picked cell to that location given the room.
	void moveToPosition(List<Point>^ movementPath);
	// Swapping cells with another to get the picked pebble to move.
	void swapCell(Point^ cell1, Point^cell2);
private:
	int checkHorizontal (Point^ startPoint);
	int checkVertical (Point^ startPoint);
	int checkDiagnalLeft (Point^ startPoint);
	int checkDiagnalRight (Point^ startPoint);
	List<Point>^ neighbors (Point toCheck);

	

};

