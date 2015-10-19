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
	this->graphics = graphics;
}

void Board::saveCurrentBoardState()
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
	previousBoardStates->Add(toSave);
}

void Board::revertState()
{
	if(previousBoardStates->Count != 0)
	{
		currentBoard = previousBoardStates[previousBoardStates->Count - 1];
		previousBoardStates->RemoveAt(previousBoardStates->Count - 1);
	}
}

void Board::addThree(Random^ rand)
{
	for(int i = 0; i < 3; i++)
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
