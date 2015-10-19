#pragma once
#include "Cell.h"
#define CELLWIDTH 40
using System::Random;

using System::Collections::Generic::List;

ref class Board
{
private:
	array<Cell^,2>^ currentBoard;
	List<array<Cell^,2>^>^ previousBoardStates;
	Graphics^ graphics;
	
public:
	Board(Graphics^ graphics);
	void saveCurrentBoardState();
	void revertState();
	void addThree(Random^ rand);
	Cell^ getBoardCell(int X, int Y);
	Cell^ getBoardCell(Point^ cell);
	void drawCells();

};
