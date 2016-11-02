#include "stdafx.h"
#include "Timer.h"
#include "assert.h"

using namespace CommonUtilities;

Timer::Timer(Clocks aClock)
:myTotalTime(aClock,0),
myTimeSinceLastUpdate(aClock,0)
{
	myClockIdentity = aClock;
	myIsPausedFlag=false;
}
	
Timer::~Timer()
{
}

void Timer::AttachTimer(Timer* aTimer)
{
	myAttachedTimers.push_back(aTimer);
}

bool Timer::Update(Time& aElapsedTime)
{
	if(myIsPausedFlag == false)
	{
		myTotalTime+=aElapsedTime.GetTime();
		myTimeSinceLastUpdate=aElapsedTime.GetTime();

		for(unsigned int counter = 0; counter < myAttachedTimers.size(); counter++)
			myAttachedTimers[counter]->Update(aElapsedTime);
	}
	else
	{
		myTotalTime+=aElapsedTime.GetTime();
		myTimeSinceLastUpdate = 0.0f;
	}
	return(true);
}

bool Timer::Update()
{
	assert(false && "Called update without defining which clock to update!");
	return(false);
}

void Timer::SetPauseState(bool aPausedFlag) 
{
	myIsPausedFlag=aPausedFlag;
}

const Time& Timer::GetTotalTime() const
{	
	return(myTotalTime);
}

const Time& Timer::GetElapsedTime() const
{
	return(myTimeSinceLastUpdate);
}
