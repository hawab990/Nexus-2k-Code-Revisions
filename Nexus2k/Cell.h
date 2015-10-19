#pragma once
#include "cellImages.h"
#include "CellColour.h"
#define CELLWIDTH 40

using namespace System::Drawing;
// a list of methods the and what it takes.

ref class Cell
{
	private:
	CellColour colour;
	Graphics^ graphics;
public:
	property bool matched;
	

public:
	Cell(CellColour colour, Graphics^ graphics);
	void drawCell(Point^ drawPosition);
	void changeCellColour(CellColour colour);
	
	CellColour GetColour();
	
	~Cell(void);

};
