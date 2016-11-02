#pragma once
#include <vector>
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
	std::vector<Worker> myWorkers;
	std::queue<const Work*> myWork;
	std::thread * myThread;
	std::mutex myThreadLock;
	volatile bool myShouldRun;

	void DistributeWork();
	void AssignWork(const Work & someWork);
	void KillWorkers();
};

