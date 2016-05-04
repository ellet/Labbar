#pragma once
#include "../GrowingArray/GrowingArray.h"
#include "ThreadData.h"

namespace std
{
	class thread;
}

class Syncronizer
{
public:
	Syncronizer();
	~Syncronizer();

	inline void ContinueAllMyThreads();
	void inline WaitForAllMyThreads();

	void inline AddThread(ThreadData * const aThreadDataToAdd);

	bool inline AllThreadsShouldRun();

	void inline Quit();

private:
	volatile bool myThreadsShouldRun;

	CU::GrowingArray<ThreadData*> myThreads;
};


void Syncronizer::AddThread(ThreadData * const aThreadDataToAdd)
{
	myThreads.Add(aThreadDataToAdd);
}

bool Syncronizer::AllThreadsShouldRun()
{
	return myThreadsShouldRun;
}

void Syncronizer::Quit()
{
	myThreadsShouldRun = false;
}

inline void Syncronizer::ContinueAllMyThreads()
{
	for (unsigned short iThread = 0; iThread < myThreads.Size(); ++iThread)
	{
		myThreads[iThread]->RunThread();
	}
}

inline void Syncronizer::WaitForAllMyThreads()
{
	for (unsigned short iThread = 0; iThread < myThreads.Size(); ++iThread)
	{
		while (myThreads[iThread]->GetIfThreadIsDoneWithFrame() == false)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	
}