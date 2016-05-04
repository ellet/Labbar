// ThePartyPoolWithTheWorkersThatAreWorking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <sstream>
#include <thread>
#include <fstream>
#include <ThreadPool/ThreadPool.h>
#include <ThreadPool/Work.h>
#include <functional>
#include <iostream>

void FunctionThatPrintsToFile(const std::string aFilePath, const std::string & aMessage)
{
	std::ofstream toWriteTo(aFilePath);
	for (size_t iDerp = 0; iDerp < 10000; ++iDerp)
	{
		toWriteTo << aMessage << iDerp << std::endl;
	}
	toWriteTo.close();
}


int _tmain(int argc, _TCHAR* argv[])
{
	ThreadPool prettyPool;

	std::stringstream streamy;
	CU::GrowingArray<Work*> toDo;
	toDo.Init(1000);

	std::cout << "The workers are creating text files in the folder 'outputFolder'.\nEach text file represents an instance of work.\nThe program will stop when 1000 files are made, or when you press a key.\n" << std::endl;

	for (int iWork = 0; iWork < 1000; ++iWork)
	{
		streamy << "outputFolder/Work" << iWork << ".txt";
		WorkFunction durr = std::bind(FunctionThatPrintsToFile, streamy.str(), "Count");
		toDo.Add(new Work(durr));
		prettyPool.AddWork(*toDo.GetLast());
		streamy.clear();
		streamy.str(std::string());
	}


	system("pause");

	prettyPool.Stop();

	return 0;
}

