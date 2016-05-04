#pragma once
#include <thread>



class ThreadData
{
public:
	ThreadData()
	{
		myThread = nullptr;
		myIsDone = false;
		myIShouldRun = false;
	}

	inline void RunThread();
	inline void DoneThread();
	inline void StartedWorking();
	inline void SetThread(std::thread * const aThread);

	inline bool GetIfThreadIsDoneWithFrame();

	inline void WaitForOtherThreadsToBedone();

private:
	std::thread * myThread;
	volatile bool myIsDone;
	volatile bool myIShouldRun;
};

inline void ThreadData::RunThread()
{
	myIsDone = false;
	myIShouldRun = true;
}

inline void ThreadData::DoneThread()
{
	myIsDone = true;
}

void ThreadData::StartedWorking()
{
	myIShouldRun = false;
}

inline void ThreadData::SetThread(std::thread * const aThread)
{
	myThread = aThread;
}


inline bool ThreadData::GetIfThreadIsDoneWithFrame()
{
	return myIsDone;
}

inline void ThreadData::WaitForOtherThreadsToBedone()
{
	while (myIShouldRun == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	};
}
