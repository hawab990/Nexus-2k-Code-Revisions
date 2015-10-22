#include "StdAfx.h"
#include "Board.h"

Board::Board(Graphics^ graphics)
{
	currentBoard = gcnew array<Cell^,2>(9,9);
	for(int row = 0; row < 9; row++)
	{
		for(int collum = 0; collum < 9; collum++)
		{
			//Creating the cells on the graphics.
			currentBoard[row,collum] = gcnew Cell(CellColour::free, graphics);
		}
	}
	previousBoardStates = gcnew List<array<Cell^,2>^>();
	this->previousScore= gcnew List<int>();
	this->graphics = graphics;
}

void Board::saveCurrentBoardState(int score)
{
	array<Cell^,2>^ toSave = gcnew array<Cell^,2>(9,9);
	for(int row = 0; row < 9; row++)
	{
		for(int collum = 0; collum < 9; collum++)
		{
			//Creating the cells on the graphics.
			toSave[row,collum] = gcnew Cell(currentBoard[row,collum]->GetColour(), graphics);
		}
	}
	//Takes a previous snap show of the board state, and its score.
	previousBoardStates->Add(toSave);
	this->previousScore->Add(score);

}

int Board::revertState()
{// setting the current board layout with the previous one.
	if(previousBoardStates->Count != 0)
	{
		// Get the last item in the last item in previous states, and set that to the current state.
		currentBoard = previousBoardStates[previousBoardStates->Count - 1];
		previousBoardStates->RemoveAt(previousBoardStates->Count - 1);
		//Set your score to be the score of the preivous state.
		int temp= previousScore[previousScore->Count - 1];
		previousScore->RemoveAt(previousScore->Count - 1);
		return temp;
	}
	return 0;
}

bool Board::addThree(Random^ rand)
{
	bool gameOver=false;
	//Loops through and adds three pebbles, and do that loop until you got three, and once game= true.
	for(int i = 0; i < 3 && gameOver==false; i++)
	{
		// Checks prior to putting in each pebble to see if there is a free space.
		if (isfull())
		{
			gameOver=true;

		}
		else
		{
			int row;
			int collum;
			do{
				row = rand->Next(9);
				collum = rand->Next(9);
			} while( currentBoard[collum, row]->GetColour() != CellColour::free);

			CellColour newCellColour;
			do
			{
				newCellColour = (CellColour)rand->Next(8);
			} while (newCellColour == CellColour::free || newCellColour == CellColour::moveable);


			currentBoard[collum, row]->changeCellColour(newCellColour);
		}


	}	// Checking to see after having to put all three balls.
	if (isfull())
	{
		gameOver=true;
	}
	return gameOver;
}
//Looping through the entire grid and as soon as it finds any empty cells, it is going to
//terminate this loop
bool Board::isfull()
{

	for	(int row=0; row<9; row++)
	{

		for(int collum=0; collum<9; collum++)
		{
			//if the board is free and is movable then return return false.
			if (currentBoard[row,collum]->colour==CellColour::free||currentBoard[row,collum]->colour==CellColour::moveable)
			{

				return false;


			}

		}

	}
	return true;

}
//
Cell^ Board::getBoardCell(int X, int Y)
{
	return currentBoard[X,Y];
}
//Overload Method, to allow the function to take a point instead of an X and  Y
Cell^ Board::getBoardCell(System::Drawing::Point ^cell)
{
	return getBoardCell(cell->X, cell->Y);
}
void Board::drawCells()
{
	for(int row = 0; row < 9; row++)
	{
		for(int collum = 0; collum < 9; collum++)
		{

			//draws the cells to panel to the current graphics.
			currentBoard[row,collum]->drawCell(gcnew Point(row * CELLWIDTH, collum * CELLWIDTH));
		}
	}
}
