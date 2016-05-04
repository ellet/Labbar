// Debugger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DL_Debug.h"



using namespace DL_Debug;

void main()
{
	Debug::Create(L"Custom_Folder_Containing_Debug_Logs");
	DL_PRINT("This is a text printed by DL_PRINT");
	int blaha = 8;
	float derpDerp = 1.f;
	std::string thisString = "Apa";
	DL_DEBUG("This is a debug message printed by DL_DEBUG - Tests:   int : %i   float:  %f  string: %s   ", blaha, derpDerp, thisString.c_str());

	DL_ASSERT(false, "This is a message printed by DL_ASSERT");
}

