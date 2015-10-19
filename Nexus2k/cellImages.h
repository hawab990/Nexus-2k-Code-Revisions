#pragma once
using namespace System::Drawing;

public enum class CellColour {free, moveable, red, blue, green, pink, lightBlue, yellow, selected};

ref class cellImages
{
private:
	 static array<Image^>^ images;
	 cellImages(void);
	 static cellImages^ selfInstance;

public:
	
	 ~cellImages(void);
	// Method to load images
	 void loadImages();
	 static Image^ getCellImage(CellColour colour);
	
};
