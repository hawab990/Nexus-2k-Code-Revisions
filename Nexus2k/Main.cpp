#include "StdAfx.h"
#include "Main.h"

Main::Main(Graphics^ graphics)
{
	board=gcnew Board(graphics);
	utilityActual=gcnew Utilities(board);
	random=gcnew Random();
	score=0;
	board->addThree(random);
	board->addThree(random);
	this->graphics = graphics;
	currentlyMoving = false;
}

	
void Main::playTurn()
{
}
void Main::undo()
{
	board->revertState();
}
void Main:: draw()
{
	board->drawCells();
	utilityActual->drawPossibleMoves(graphics);
	if(utilityActual->pickedCell != nullptr)
	{
		graphics->DrawImage(cellImages::getCellImage(CellColour::selected), utilityActual->pickedCell->X*CELLWIDTH, utilityActual->pickedCell->Y*CELLWIDTH, CELLWIDTH,CELLWIDTH);
	}	
}


void Main:: click(Point^ clickLocation)
{
	// Clicked location in the cell array
	Point^ newClickedCellLocation= gcnew Point(clickLocation->X/CELLWIDTH, clickLocation->Y/CELLWIDTH);
	//if we havnt picked it a cell its empty.
	if (utilityActual->pickedCell==nullptr && board->getBoardCell(newClickedCellLocation)->GetColour()!= CellColour::free)//Converting from the screen location to the array location.
	{		
		utilityActual->pickedCell=newClickedCellLocation;
	}
	// To check if a cell is selected
	else if(utilityActual->pickedCell!=nullptr)
	{		
		if(utilityActual->pickedCell->Equals(newClickedCellLocation))
		{
			// if the cell is selected cell is clicked, then unselect it.
				utilityActual->pickedCell=nullptr;
		}
			// if the selected cell is not cell previously selected then swapping to the free cell.
		else if (board->getBoardCell(newClickedCellLocation)->GetColour()==CellColour::free)
		{
			//Move cell to new location.
			List<Point>^ pathToD = utilityActual->findMovementPath(newClickedCellLocation);
			if(pathToD->Count > 0)
			{
				SystemSounds::Asterisk->Play();
				board->saveCurrentBoardState();
				currentlyMoving = true;
				utilityActual->pickedCell = nullptr;
				utilityActual->moveToPosition(pathToD);

				//Check for rows of 5
				score += utilityActual->detectFive();
				currentlyMoving = false;
				board->addThree(random);
			}
		}
		else 
		{
			utilityActual->pickedCell=newClickedCellLocation;
		}	
	}
}


