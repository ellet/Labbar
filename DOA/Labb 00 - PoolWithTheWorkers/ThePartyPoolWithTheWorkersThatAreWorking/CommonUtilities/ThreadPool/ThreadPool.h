#pragma once
#include "../GrowingArray/GrowingArray.h"
#include "../NameSpaceAliases.h"
#include "Worker.h"
#include <queue>
#include <mutex>

class Work;

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void AddWork(const Work & someWork);
	void Stop();

private:
	CU::GrowingArray<Worker> myWorkers;
	std::queue<const Work*> myWork;
	std::thread * myThread;
	std::mutex myThreadLock;
	volatile bool myShouldRun;

	void DistributeWork();
	void AssignWork(const Work & someWork);
	void KillWorkers();
};

