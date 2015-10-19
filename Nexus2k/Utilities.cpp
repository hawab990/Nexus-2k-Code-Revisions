#include "StdAfx.h"
#include "Utilities.h"


// Passing in the gameboard into the constructor.
Utilities::Utilities(Board^ gameBoard)
{
	pickedCell=nullptr;
	this->gameBoard=gameBoard;

}

int Utilities:: detectFive()
{
	int sumScore=0;

	//Checks the whole board rows of repeating cells.
	for(int i=0; i<9; i++)
	{
		for(int k=0;k<9; k++)
		{
			Point^ checkCell= gcnew Point(i,k);
			sumScore+=checkHorizontal(checkCell);
			sumScore+=checkVertical(checkCell);
			sumScore+=checkDiagnalLeft(checkCell);
			sumScore+=checkDiagnalRight(checkCell);
		}

	}
	for(int row = 0; row < 9; row++)
	{
		for(int collum = 0; collum < 9; collum++)
		{
			if(gameBoard->getBoardCell(row,collum)->matched == true)
			{
				gameBoard->getBoardCell(row,collum)->changeCellColour(CellColour::free);
				gameBoard->getBoardCell(row,collum)->matched = false;
			}
		}
	}
	return sumScore;
}
void Utilities:: drawPossibleMoves(Graphics^ graphics)
{
	if(pickedCell == nullptr) 
	{
		return;
	}
	//check if a cell is next to where you want to go, is free and no visited. Go to that.
	//
	Queue<Point>^ frontier = gcnew Queue<Point>();
	frontier->Enqueue(Point(pickedCell->X, pickedCell->Y));
	// Dictionary holding indexes to multiple datatypes. Point is the index and the bool is the data type at the location index.

	Dictionary<Point, bool>^ visited = gcnew Dictionary<Point, bool>();
	visited->Add(Point(pickedCell->X, pickedCell->Y), true);

	while(frontier->Count > 0)
	{
		// Taking a point from the que of points.
		Point current = frontier->Dequeue();
		for each(Point next in neighbors(current))
		{
			// Check if the dictionary contains a value for the given point, and if it does not, add it to the queue to visit later
			if(!visited->ContainsKey(next))
			{
				frontier->Enqueue(next);
				visited->Add(next, true);
			}
		}
	}
	// Draw all of cells that are possible to visit
	for each (Point itemToDraw in visited->Keys)
	{
		graphics->DrawImage(cellImages::getCellImage(CellColour::moveable), itemToDraw.X*CELLWIDTH, itemToDraw.Y*CELLWIDTH, CELLWIDTH,CELLWIDTH);
	}



}
List<Point>^ Utilities::neighbors (Point toCheck)
{
	List<Point>^ toReturn = gcnew List<Point>();
	array<Point^>^ pointsToCheck = {
		gcnew Point(toCheck.X, toCheck.Y-1), gcnew Point(toCheck.X-1, toCheck.Y), gcnew Point(toCheck.X+1, toCheck.Y), gcnew Point(toCheck.X, toCheck.Y+1)
	};

	for each(Point^ itemCurrentlyChecked in pointsToCheck)
	{
		if(itemCurrentlyChecked->X>8||itemCurrentlyChecked->X<0 || itemCurrentlyChecked->Y>8||itemCurrentlyChecked->Y<0)
		{
			// Prematurely ends current loop iteration because the point is out of bounds.
			continue;
		}
		if(gameBoard->getBoardCell(itemCurrentlyChecked)->GetColour() == CellColour::free)
		{
			toReturn->Add(Point(itemCurrentlyChecked->X, itemCurrentlyChecked->Y));
		}
	}
	return toReturn;
}
List<Point>^ Utilities::findMovementPath(Point^ endPoint)
{
	List<Point>^ toReturn = gcnew List<Point>();

	if(pickedCell == nullptr) 
	{
		return toReturn;
	}
	//check if a cell is next to where you want to go, is free and no visited. Go to that.
	//The camefrom cells point to the cell previous in its traversal.
	Queue<Point>^ frontier = gcnew Queue<Point>();
	frontier->Enqueue(Point(pickedCell->X, pickedCell->Y));
	// Dictionary holding indexes to multiple datatypes. Point is the index and the bool is the data type at the location index.

	Dictionary<Point, Point>^ cameFrom = gcnew Dictionary<Point, Point>();
	//cameFrom->Add(Point(pickedCell->X, pickedCell->Y), nullptr);

	while(frontier->Count > 0)
	{
		// Taking a point from the que of points.
		Point current = frontier->Dequeue();
		for each(Point next in neighbors(current))
		{
			// Check if the dictionary contains a value for the given point, and if it does not, add it to the queue to visit later
			if(!cameFrom->ContainsKey(next))
			{
				frontier->Enqueue(next);
				cameFrom->Add(next, current);
			}
		}
	}
	if(!cameFrom->ContainsKey( Point(endPoint->X, endPoint->Y)) )
	{
		return toReturn;
	}
	{		
		Point current = Point(endPoint->X, endPoint->Y);
		toReturn->Add(current);
		while(current != Point(pickedCell->X, pickedCell->Y))
		{
			// Storing  a key to the value into the list.
			current = cameFrom[current];
			toReturn->Add(current);
		}
		toReturn->Reverse();
	}
	return toReturn;
}

//Takes one point and moves picked cell to that location given the room.
void Utilities:: moveToPosition(List<Point>^ movementPath)
{
	int count = movementPath->Count;
	for(int i = 1; i < movementPath->Count; i++)
	{
		Point^ firstPoint = gcnew Point(movementPath[i-1].X,movementPath[i-1].Y);
		Point^ secondPoint = gcnew Point(movementPath[i].X,movementPath[i].Y);
		swapCell(firstPoint, secondPoint);
	}
 
}
// Swapping cells with another to get the picked pebble to move.
void Utilities:: swapCell(Point^ cell1, Point^cell2)
{
	//Go to the gameBoard, retrieve the cell at X and Y and the colour.
	CellColour temp=gameBoard->getBoardCell(cell1->X,cell1->Y)->GetColour();
	//Sets cell 1's colour to cell 2's colour.
	gameBoard->getBoardCell(cell1->X,cell1->Y)->changeCellColour(gameBoard->getBoardCell(cell2->X,cell2->Y)->GetColour());
	gameBoard->getBoardCell(cell2->X,cell2->Y)->changeCellColour(temp);
}
//The Path Finding Goes here!



int Utilities::checkHorizontal (Point^ startPoint)
{
	List<Cell^>^ checkedCells = gcnew List<Cell^>();

	int cellCount=1;
	// Saving the colour of the first and the if statement checks if its empty. And it doesnt run the rest of the method.

	CellColour startCellColour=gameBoard->getBoardCell(startPoint->X, startPoint->Y)->GetColour();
	checkedCells->Add(gameBoard->getBoardCell(startPoint->X, startPoint->Y));//
	Point^ nextPoint=gcnew Point(startPoint->X, startPoint->Y);
	if(startCellColour==CellColour::free)
	{
		return 0;

	}
	bool repeatFound=false;
	do{

		// Creates a new point, gets the cell at that point and checks its colour.
		nextPoint->X++;

		if(nextPoint->X==9)
		{
			break;
		}
		//Then compares the colour of the next point accross the X axis, and if its the same colour the Cell count will be incremented.
		if(startCellColour==gameBoard->getBoardCell(nextPoint->X, nextPoint->Y)->GetColour())
		{
			cellCount++;
			repeatFound=true;
			checkedCells->Add(gameBoard->getBoardCell(nextPoint->X, nextPoint->Y));//
		}
		else 
		{
			// If no match has been found, terminate at this statement.
			repeatFound=false;
		}
	}
	while(repeatFound);	
	if(cellCount < 5)
	{
		return 0;
	}
	else
	{
		for each(Cell^ item in checkedCells)
		{
			item->matched = true;
		}
		return cellCount*10; // return when 5 or more cells found
	}
}
int Utilities::checkVertical (Point^ startPoint)
{
	List<Cell^>^ checkedCells = gcnew List<Cell^>();

	int cellCount=1;
	// Saving the colour of the first and the if statement checks if its empty. And it doesnt run the rest of the method.

	CellColour startCellColour=gameBoard->getBoardCell(startPoint->X, startPoint->Y)->GetColour();
	checkedCells->Add(gameBoard->getBoardCell(startPoint->X, startPoint->Y));//
	Point^ nextPoint=gcnew Point(startPoint->X, startPoint->Y);
	if(startCellColour==CellColour::free)
	{
		return 0;

	}
	bool repeatFound=false;
	do{
		// Creates a new point, gets the cell at that point and checks its colour.
		nextPoint->Y++;
		if(nextPoint->Y==9)
		{
			break;
		}
		//Then compares the colour of the next point accross the X axis, and if its the same colour the Cell count will be incremented.
		if(startCellColour ==gameBoard->getBoardCell(nextPoint->X, nextPoint->Y)->GetColour())
		{
			cellCount++;
			repeatFound=true;
			checkedCells->Add(gameBoard->getBoardCell(nextPoint->X, nextPoint->Y));//
		}
		else 
		{
			// If no match has been found, terminate at this statement.
			repeatFound=false;
		}
		
	}
	while(repeatFound);	
	if(cellCount < 5)
	{
		return 0;
	}
	else
	{
		for each(Cell^ item in checkedCells)
		{
			item->matched = true;
		}
		return cellCount*10; // return when 5 or more cells found
	}
}
int Utilities::checkDiagnalRight (Point^ startPoint)
{
	List<Cell^>^ checkedCells = gcnew List<Cell^>();
	int cellCount=1;
	// Saving the colour of the first and the if statement checks if its empty. And it doesnt run the rest of the method.

	CellColour startCellColour=gameBoard->getBoardCell(startPoint->X, startPoint->Y)->GetColour();
	checkedCells->Add(gameBoard->getBoardCell(startPoint->X, startPoint->Y));//
	Point^ nextPoint=gcnew Point(startPoint->X, startPoint->Y);
	if(startCellColour==CellColour::free)
	{
		return 0;

	}
	bool repeatFound=false;
	do{
		// Creates a new point, gets the cell at that point and checks its colour.
		//given a position of a point, go down Y++ and right X-- in a diagnal manner.
		nextPoint->X++;
		nextPoint->Y++;
		// Checks if its passed outermost boundry.
		if(nextPoint->X==9 || nextPoint->Y==9)
		{
			break;
		}
		//Then compares the colour of the next point accross the X axis, and if its the same colour the Cell count will be incremented.
		if(startCellColour==gameBoard->getBoardCell(nextPoint->X, nextPoint->Y)->GetColour())
		{
			cellCount++;
			repeatFound=true;
			checkedCells->Add(gameBoard->getBoardCell(nextPoint->X, nextPoint->Y));//
		}
		else 
		{
			// If no match has been found, terminate at this statement.
			repeatFound=false;
		}
	}
	while(repeatFound);	
	if(cellCount < 5)
	{
		return 0;
	}
	else
	{
		for each(Cell^ item in checkedCells)
		{
			item->matched = true;
		}
		return cellCount*10; // return when 5 or more cells found
	}
}
int Utilities::checkDiagnalLeft (Point^ startPoint)
{
	List<Cell^>^ checkedCells = gcnew List<Cell^>();



	int cellCount=1;
	// Saving the colour of the first and the if statement checks if its empty. And it doesnt run the rest of the method.

	CellColour startCellColour=gameBoard->getBoardCell(startPoint->X, startPoint->Y)->GetColour();
	checkedCells->Add(gameBoard->getBoardCell(startPoint->X, startPoint->Y));//
	Point^ nextPoint=gcnew Point(startPoint->X, startPoint->Y);
	if(startCellColour==CellColour::free)
	{
		return 0;

	}
	bool repeatFound=false;
	do{
		// Creates a new point, gets the cell at that point and checks its colour.
		//given a position of a point, go down Y++ and left X-- in a diagnal manner.
		nextPoint->X--;
		nextPoint->Y++;
		// Checks if its passed the left outmost boundry -1, and the bottom of the container 9
		if(nextPoint->X==-1 || nextPoint->Y==9)
		{
			break;
		}
		//Then compares the colour of the next point accross the X axis, and if its the same colour the Cell count will be incremented.
		if(startCellColour==gameBoard->getBoardCell(nextPoint->X, nextPoint->Y)->GetColour())
		{
			cellCount++;
			repeatFound=true;
			checkedCells->Add(gameBoard->getBoardCell(nextPoint->X, nextPoint->Y));//
		}
		else 
		{
			// If no match has been found, terminate at this statement.
			repeatFound=false;
		}
	}
	while(repeatFound);	
	if(cellCount <5)
	{
		return 0;
	}
	else
	{
		for each(Cell^ item in checkedCells)
		{
			item->matched = true;
		}
		
		return cellCount*10; // return when 5 or more cells found
	}
}


