#pragma once

namespace std
{
	class thread;
}
class Work;

class Worker
{
public:
	Worker();
	~Worker();

	void AssignWork(const Work & someWork);

	void Join();
	void Stop();

	bool IsWorking();

private:
	std::thread * myThread;
	const Work * myWork;
	volatile bool myIsWorking;
	volatile bool myShouldRun;

	void WorkerThread();

};

