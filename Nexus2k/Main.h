#include "Board.h"
#include "CellColour.h"
#include "Utilities.h"
#include "Cell.h"
#define CELLWIDTH 40
using namespace System::Drawing;
using namespace System::Media;
#pragma once

public ref  class Main
{
public:
	property int score;
private:
	Board^ board;
	
	Random^ random;
	Utilities^ utilityActual;
	Graphics^ graphics;
	bool currentlyMoving;


	


public:
	Main(Graphics^ graphics);
	void playTurn();
	void undo();
	void draw();
	void click(Point^ clickLocation);

};
