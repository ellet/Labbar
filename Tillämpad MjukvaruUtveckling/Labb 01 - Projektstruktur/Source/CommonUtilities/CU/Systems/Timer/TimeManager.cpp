#include "stdafx.h"
#include "TimeManager.h"
#include "TimeManagerTimeStamps.h"

namespace CommonUtilities
{

	TimeManager * TimeManager::ourInstance;

	void TimeManager::Create()
	{
		if (ourInstance == nullptr)
		{
			ourInstance = new TimeManager();
		}
	}

	void TimeManager::Destroy()
	{
		delete ourInstance;
		ourInstance = nullptr;
	}


	void TimeManager::Update()
	{
		GetInstance().DoUpdate();
	}


	void TimeManager::DoUpdate()
	{
		if (myImPaused == false)
		{
			QueryPerformanceCounter(&myStamps->myCurrentStamp);
			myStamps->myTimeDifference.QuadPart = static_cast<LONGLONG>((myStamps->myCurrentStamp.QuadPart - myStamps->myCountFromStamp.QuadPart) / (myFrequency));
			myDeltaTime = static_cast<LONGLONG>((myStamps->myCurrentStamp.QuadPart - myStamps->myPreviousStamp.QuadPart) / (myFrequency));

			myStamps->myPreviousStamp = myStamps->myCurrentStamp;
		}
	}

	 Time TimeManager::GetDeltaTime()
	{
		/*if (GetInstance().myDeltaTime / 1000000.0 >= 1)
		{
			return Time(0);
		}*/
		return Time(GetInstance().myDeltaTime);
	}

	/*size_t TimeManager::CreateNewTimer()
	{
		GetInstance().myTimers.push_back(Timer(GetInstance().myTimeDifference.QuadPart));
		return GetInstance().myTimers.size() - 1;
	}*/

	LONGLONG TimeManager::GetTimeSinceStart()
	{
		return  static_cast<LONGLONG>((static_cast<double>(GetInstance().myStamps->myTimeDifference.QuadPart) / 1000000.0));
	}

	LONGLONG TimeManager::GetMainStamp()
	{
		return GetInstance().myStamps->myTimeDifference.QuadPart;
	}

	/*Timer & TimeManager::GetTimer(size_t aTimerIndex)
	{
		return GetInstance().myTimers[aTimerIndex];
	}*/

	const Time & TimeManager::GetTimerTime(size_t aTimerIndex)
	{
		return GetInstance().myTimers[aTimerIndex].GetTime();
	}

	void TimeManager::PauseAllTimers()
	{
		GetInstance().DoPauseAllTimers();
	}

	void TimeManager::ResumeAllTimers()
	{
		GetInstance().DoResumeAllTimers();
	}
	

	void TimeManager::DoPauseAllTimers()
	{
		if (myImPaused == false)
		{
			myImPaused = true;
			QueryPerformanceCounter(&myStamps->myPauseStamp);
		}
	}

	void TimeManager::DoResumeAllTimers()
	{
		if (myImPaused == true)
		{
			myImPaused = false;
			LARGE_INTEGER tempCounter;
			QueryPerformanceCounter(&tempCounter);
			myStamps->myCountFromStamp.QuadPart = myStamps->myCountFromStamp.QuadPart + (tempCounter.QuadPart + myStamps->myPauseStamp.QuadPart);
		}
	}



	TimeManager::TimeManager()
	{
		myStamps = new TimeManagerTimeStamps();

		LARGE_INTEGER tempGetFrequency;
		QueryPerformanceFrequency(&tempGetFrequency);
		QueryPerformanceCounter(&myStamps->myStartStamp);
		myStamps->myPreviousStamp = myStamps->myStartStamp;
		myStamps->myCurrentStamp = myStamps->myStartStamp;
		myStamps->myCountFromStamp = myStamps->myStartStamp;

		myImPaused = false;

		myFrequency = static_cast<double>(tempGetFrequency.QuadPart) / 1000000.0;
	}


	TimeManager::~TimeManager()
	{
		delete myStamps;
		myStamps = nullptr;
	}

}
