#include "stdafx.h"
#include "PrinterClass.h"

PrinterClass * PrinterClass::ourInstance = nullptr;

void PrinterClass::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new PrinterClass();
	}
	GetInstance().myNumberOfDeadUnits = 0;
}

void PrinterClass::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}



PrinterClass::PrinterClass()
{
	std::string tempFile = "DAGREATBATTLEOUTPUT.txt";
	myOutput = std::ofstream(tempFile);
}


PrinterClass::~PrinterClass()
{
	myOutput.close();
}
