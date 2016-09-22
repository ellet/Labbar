#include "stdafx.h"
#include "ThreadPool.h"
#include <thread>

ThreadPool::ThreadPool()
{
	myShouldRun = true;
	size_t numberOfCores = std::thread::hardware_concurrency();

	myWorkers.resize(static_cast<unsigned short>(numberOfCores));

	myThread = new std::thread(&ThreadPool::DistributeWork, this);
}

ThreadPool::~ThreadPool()
{
	delete myThread;
	myThread = nullptr;
}

void ThreadPool::AddWork(const Work & someWork)
{
	myThreadLock.lock();
	myWork.push(&someWork);
	myThreadLock.unlock();
}

void ThreadPool::Stop()
{
	myShouldRun = false;
	myThread->join();
}

void ThreadPool::DistributeWork()
{
	while (myShouldRun == true)
	{
		if (myWork.size() > 0)
		{
			myThreadLock.lock();
			const Work * tempWork = myWork.front();
			myWork.pop();
			myThreadLock.unlock();
			AssignWork(*tempWork);
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	KillWorkers();
}

void ThreadPool::AssignWork(const Work & someWork)
{
	bool hasFoundWorker = false;
	while (hasFoundWorker == false)
	{
		for (unsigned short iWorker = 0; iWorker < myWorkers.size(); ++iWorker)
		{
			if (myWorkers[iWorker].IsWorking() == false)
			{
				myWorkers[iWorker].AssignWork(someWork);
				return;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void ThreadPool::KillWorkers()
{
	for (unsigned short iWorker = 0; iWorker < myWorkers.size(); ++iWorker)
	{
		myWorkers[iWorker].Stop();
	}
	for (unsigned short iWorker = 0; iWorker < myWorkers.size(); ++iWorker)
	{
		myWorkers[iWorker].Join();
	}
}
