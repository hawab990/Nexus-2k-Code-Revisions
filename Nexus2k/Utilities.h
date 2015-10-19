#pragma once
#include "Board.h"
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Threading;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System;

ref class Utilities
{
	public: property Point^ pickedCell;
private:
	
	Board^ gameBoard;


public:
	List<int>^ highScore();
	void highScoreList(int Score);
	Utilities(Board^ gameBoard);
	int detectFive();
	void drawPossibleMoves(Graphics^ graphics);
	List<Point>^ findMovementPath(Point^ endPoint);
	//Takes one point and moves picked cell to that location given the room.
	// Swapping cells with another to get the picked pebble to move.
	void swapCell(Point^ cell1, Point^cell2);
	void wipeScore();
	void stepAnimation(List<Point>^ pathToD, int stepIndex);
private:
	int checkHorizontal (Point^ startPoint);
	int checkVertical (Point^ startPoint);
	int checkDiagnalLeft (Point^ startPoint);
	int checkDiagnalRight (Point^ startPoint);
	List<Point>^ neighbors (Point toCheck);


	

};

