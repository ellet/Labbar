#include "stdafx.h"
#include "Timer.h"
#include "CU/Systems/MainSingleton/MainSingleton.h"
#include "TimeManager.h"
#include "../DLDebug/DL_Debug.h"

namespace CommonUtilities
{
	Timer::Timer() : myTime(0)
	{
		myTimeStamp = MainSingleton::GetTimerManager().GetMainStamp();

		myPauseStamp = myTimeStamp;
		myImPaused = false;
	}

	Timer::~Timer()
	{
	}

	void Timer::PauseTimer()
	{
		if (myImPaused == false)
		{
			myImPaused = true;
			myPauseStamp = MainSingleton::GetTimerManager().GetMainStamp();
		}
	}

	void Timer::UnpauseTimer()
	{
		if (myImPaused == true)
		{
			myImPaused = false;
			myTimeStamp += (MainSingleton::GetTimerManager().GetMainStamp() - myPauseStamp);
		}
	}

	const Time & Timer::GetTime()
	{
		if (myImPaused == false)
		{
			SetTime(MainSingleton::GetTimerManager().GetMainStamp() - myTimeStamp);
		}
		else
		{
			SetTime(myPauseStamp - myTimeStamp);
		}

		return myTime;
	}

	void Timer::SetTime(LONGLONG aTimeStamp)
	{
		myTime.SetTime(aTimeStamp);
	}

	void Timer::Reset()
	{
		myTimeStamp = MainSingleton::GetTimerManager().GetMainStamp();
	}
}