#include "DataRace.h"
#include <iostream>       // std::cout

#include <windows.h>

std::vector<int> myVector;
volatile bool doRun = false;


void TheFunc(int aStartVal, int aMax)
{
	while (doRun == false)
	{
		Sleep(10);
		continue;
	}
	for (int i = aStartVal; i < aMax; i++)
	{
		myVector[i] = i;
	}
	
}


CDataRace::CDataRace(unsigned int aThreadNumber)
{
	myVector.resize(aThreadNumber * 50);
	myThreads.reserve(aThreadNumber);
	for (unsigned int i=0; i< aThreadNumber; i++)
	{
		try {
			std::thread* thread = new std::thread(TheFunc, (i * 50), (i * 50) + 50);
			myThreads.push_back(thread);

		}
		catch (const std::system_error& e) {
			
			std::cout << "Too many threads. I cannot handle. Hlep meh. Probably not enough memory for stack." << std::endl;

		}
	}
}



CDataRace::~CDataRace()
{
}

void CDataRace::Run()
{
	doRun = true;

	for (unsigned int i = 0; i < myThreads.size(); i++)
	{
		myThreads[i]->join();
		delete (myThreads[i]);
	}

	for (int vectorIndex : myVector)
	{
		std::cout << vectorIndex << "\n";
	}


	
}
