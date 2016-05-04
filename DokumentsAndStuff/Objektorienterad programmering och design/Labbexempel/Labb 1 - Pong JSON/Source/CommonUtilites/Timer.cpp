#include "stdafx.h"
#include "Timer.h"

namespace CommonUtilities
{
	Timer::Timer()
	{
		myLifeTime = 0;
		myDeltaTime = 0;
		myOn = true;
	}

	Timer::~Timer(void)
	{
	}

	void Timer::AddTime(const TimeUnit aTime)
	{
		if (myOn == true)
		{
			myLifeTime += aTime;
			myDeltaTime = aTime;
		}
	}
}