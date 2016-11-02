#include <Precompiled.h>
#include "TI_Timer.h"

using namespace TI_Time;

Timer::Timer(Clocks aClock)
:myCurrentTime(aClock,0),
myElapsedTime(aClock,0)
{
	myIsPausedFlag=false;
	myAttachedTimers.Init(24,12);
}
	
Timer::~Timer()
{
}

void Timer::AttachTimer(Timer* aTimer)
{
	myAttachedTimers.Add(aTimer);
}

bool Timer::Update(Time& aElapsedTime)
{
	if(false==myIsPausedFlag)
	{
		myCurrentTime+=aElapsedTime;
		myElapsedTime=aElapsedTime;

		for(int counter = 0; counter < myAttachedTimers.Count(); counter++)
		{
			myAttachedTimers[counter]->Update(aElapsedTime);
		}
	}
	else
	{
		myElapsedTime = 0.0f;
	}
	return(true);
}

void Timer::SetPauseState(bool aPausedFlag) 
{
	myIsPausedFlag=aPausedFlag;
	if(aPausedFlag == true)
	{
		ClearElapsedTime();
		for(int counter = 0; counter < myAttachedTimers.Count(); counter++)
		{
			myAttachedTimers[counter]->ClearElapsedTime();
		}
	}

}

const Time& Timer::GetTotalTime() const
{	
	return(myCurrentTime);
}

const Time& Timer::GetElapsedTime() const
{
	return(myElapsedTime);
}

void Timer::ClearElapsedTime()
{
	myElapsedTime = 0.0f;
}
