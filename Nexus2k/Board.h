#pragma once
#include "Cell.h"
#define CELLWIDTH 40
using System::Random;
using namespace System::Windows::Forms;

using System::Collections::Generic::List;

ref class Board
{
private:
	array<Cell^,2>^ currentBoard;
	List<array<Cell^,2>^>^ previousBoardStates;
	List<int> ^ previousScore;
	Graphics^ graphics;
	
public:
	Board(Graphics^ graphics);
	void saveCurrentBoardState(int score);
	int revertState();
	bool addThree(Random^ rand);
	Cell^ getBoardCell(int X, int Y);
	Cell^ getBoardCell(Point^ cell);
	void drawCells();
	bool isfull();
};
