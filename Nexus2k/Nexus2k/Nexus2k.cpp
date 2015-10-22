/* Program name: 	    Nexus 2k
   Project file name: Nexus 2k-AbdelRahman Hawwari
   Author:		    AbdelRahman Hawwari
   Date:	 
   Language:		    C++
   Platform:		    Microsoft Visual Studio 2013
   Purpose:				Simulates a connect 4 like game where you have to connect 5 or more cells to score points before the grid gets completely full	    
   Known Bugs:		    N/A
   Additional Features: Clicking sound
						Allows you to wipe all high scores to start a new.
						Displays a list of high scores.
*/




// Nexus2k.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"

using namespace Nexus2k;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
