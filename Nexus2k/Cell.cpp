#include "StdAfx.h"
#include "Cell.h"
// Constructor of the nexus pieces
Cell::Cell(CellColour colour, Graphics^ graphics)
{
	this->colour=colour;
	this->graphics=graphics;
	matched = false;
}
// The name of the class follow by the name of the method
Cell::~Cell(void)
{
}
// access the cellImages class and passes in colour of the cell images you want returned.
void Cell::drawCell(Point^ drawPosition)
{
	Image^ toDraw = cellImages::getCellImage(colour);
	graphics->DrawImage(toDraw,drawPosition->X, drawPosition->Y,CELLWIDTH, CELLWIDTH);
}
// Sets the colour to a new which will be used in the swapping of adjacent colours.
void Cell::changeCellColour(CellColour colour)
{
	this->colour = colour;
}
CellColour Cell::GetColour()
{
	return colour;
}