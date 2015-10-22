#include "StdAfx.h"
#include "cellImages.h"
#include "CellColour.h"

cellImages::cellImages(void)
{
	loadImages();
}

cellImages::~cellImages(void)
{
}
void cellImages::loadImages()
{
	images = gcnew array<Image^>(9);
	images[(int)CellColour::free] = Image::FromFile("freeEmpty.png");
	images[(int)CellColour::moveable] = Image::FromFile("free.png");
	images[(int)CellColour::blue] = Image::FromFile("blue.png");
	images[(int)CellColour::green] = Image::FromFile("green.png");
	images[(int)CellColour::lightBlue] = Image::FromFile("bleau.png");
	images[(int)CellColour::pink] = Image::FromFile("purple.png");
	images[(int)CellColour::red] = Image::FromFile("red.png");
	images[(int)CellColour::yellow] = Image::FromFile("yellow.png");
	images[(int)CellColour::selected] = Image::FromFile("selected.png");

}
Image^ cellImages::getCellImage(CellColour colour)
{
	if(selfInstance == nullptr)
		//Checks if the  cellimages have been loaded.
	{
		selfInstance = gcnew cellImages();
	}
	return images[(int)colour];
}