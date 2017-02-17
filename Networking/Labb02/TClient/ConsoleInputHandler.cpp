#include "stdafx.h"
#include "ConsoleInputHandler.h"


ConsoleInputHandler::ConsoleInputHandler()
{
	myIsAlive = true;
	myIsDone = false;
}


ConsoleInputHandler::~ConsoleInputHandler()
{
	myThread->join();
	delete myThread;
	myThread = nullptr;
}

void ConsoleInputHandler::Start(const std::string & aName)
{
	myClientName = aName;
	myThread = new std::thread(&ConsoleInputHandler::ThreadUpdate, this);
}

void ConsoleInputHandler::Stop()
{
	myIsAlive = false;
}

bool ConsoleInputHandler::GetInputString(std::string & aStringToSet)
{
	if (myIsDone == true)
	{
		aStringToSet = myString;
		myIsDone = false;
		return true;
	}

	return false;
}

void ConsoleInputHandler::ThreadUpdate()
{
	while (myIsAlive == true)
	{
		if (myIsDone != true)
		{
			std::cout << myClientName << ": ";
			std::getline(std::cin, myString);
			myIsDone = true;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}
}
