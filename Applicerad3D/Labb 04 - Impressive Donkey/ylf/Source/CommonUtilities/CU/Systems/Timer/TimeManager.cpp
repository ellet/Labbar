#include "stdafx.h"
#include "TimeManager.h"
#include "TimeManagerTimeStamps.h"

namespace CommonUtilities
{

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

	void TimeManager::Update()
	{
		DoUpdate();
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

	const Time & TimeManager::GetDeltaTime()
	{
		return Time(myDeltaTime);
	}

	LONGLONG TimeManager::GetTimeSinceStart()
	{
		return  static_cast<LONGLONG>((static_cast<double>(myStamps->myTimeDifference.QuadPart) / 1000000.0));
	}

	LONGLONG TimeManager::GetMainStamp()
	{
		return myStamps->myTimeDifference.QuadPart;
	}

	const Time & TimeManager::GetTimerTime(size_t aTimerIndex)
	{
		return myTimers[aTimerIndex].GetTime();
	}

	void TimeManager::PauseAllTimers()
	{
		DoPauseAllTimers();
	}

	void TimeManager::ResumeAllTimers()
	{
		DoResumeAllTimers();
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
}
