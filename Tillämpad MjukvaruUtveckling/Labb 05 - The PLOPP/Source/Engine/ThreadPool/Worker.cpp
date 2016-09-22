#include "stdafx.h"
#include "Worker.h"
#include "Work.h"
#include <thread>

Worker::Worker()
{
	myIsWorking = false;
	myShouldRun = true;
	myWork = nullptr;
	myThread = new std::thread(&Worker::WorkerThread, this);
}

Worker::~Worker()
{
	delete myThread;
	myThread = nullptr;
}

void Worker::AssignWork(const Work & someWork)
{
	myWork = &someWork;
	myIsWorking = true;
}

void Worker::Join()
{
	myThread->join();
}

void Worker::Stop()
{
	myShouldRun = false;
}

bool Worker::IsWorking()
{
	return myIsWorking;
}

void Worker::WorkerThread()
{
	while (myShouldRun == true)
	{
		if (myIsWorking == true)
		{
			myWork->DoWork();
			myWork = nullptr;
			myIsWorking = false;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
}
