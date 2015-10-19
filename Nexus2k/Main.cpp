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
// filling in the body for that method in that class.
//wipes score upon game execution
void Main::wipeScore()
{
utilityActual->wipeScore();

}
List<int>^ Main::getHighScore(){
	return utilityActual->highScore();

}
	
void Main::playTurn()
{// check if currently moving is true
	if(currentlyMoving==true)
	{
	// Move one step along the path.
		//increment a global integer to remember the number of steps along the path.
		//utlity actual is an instance of utilities
			utilityActual->stepAnimation(pathToD, stepIndex);
			
			stepIndex++;
			//if the path is complete.
			//Set currently moving to false.
			//Calls the swap method 2 times,  for three cells hence the count-1.
			if(stepIndex>=pathToD->Count-1)
			{
		//Check for rows of 5
				score += utilityActual->detectFive();
				currentlyMoving = false;
				bool gameOver=board->addThree(random);
				score += utilityActual->detectFive();
				if(gameOver==true)
					{
						
						utilityActual->highScoreList(score);

					MessageBox::Show("Your Score is:  " + score.ToString(),"Message", MessageBoxButtons::OK);

					
				}
		
			}// Moving the pebble one step along the path.

	}
}
void Main::undo()
{
	// Getting the score back.
	score=board->revertState();
	
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
	// Disables interraction till game is out of the animation state.
	if (currentlyMoving==false)
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
			//This is saving it to the global variable rather then locally.
			 pathToD = utilityActual->findMovementPath(newClickedCellLocation);
			// there is not a path.
			if(pathToD->Count > 0)
			{
				
				SystemSounds::Asterisk->Play();
				board->saveCurrentBoardState(score);
				currentlyMoving = true;
				//Find a path, remember it and set the currentlyMoving to true.
				utilityActual->pickedCell = nullptr;
				stepIndex=0;
				
			}
		}
		else 
		{
			utilityActual->pickedCell=newClickedCellLocation;
		}	
	}
	}
}


