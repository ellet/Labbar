#include <Precompiled.h>
#include "TI_TimeManager.h"
#include "TI_Timer.h"
#include "TI_SystemTime.h"
#include "LoopMacros.h"
#include "CommonMacros.h"


using namespace TI_Time;

TimeManager *TimeManager::myInstance = NULL;
TimeManager::TimeManager()
{
	myClocks.Init(NUM_CLOCKS +2, 4);
	ForCount(NUM_CLOCKS) myClocks.Add(NULL);
	mySystemClock=NULL; // Refactor away once we gain inheritance
}

TimeManager::~TimeManager()
{
	for(int clockIndex = 0; clockIndex < myClocks.Count(); clockIndex++)
	{
		if(myClocks[clockIndex]!=NULL)
		{
			SAFE_DELETE(myClocks[clockIndex]);
		}
	}
	SAFE_DELETE(mySystemClock);
}

void TimeManager::InitDefaults()
{
	for(int i = myClocks.Count()-1; i >=0; i--)
	{
		if(myClocks[i]!=NULL)
		{
			SAFE_DELETE(myClocks[i]);
		}
	}

	

	CreateTimer(SYSTEM_CLOCK);
	CreateTimer(MASTER_CLOCK);
	AttachTimerToTimer(SYSTEM_CLOCK,MASTER_CLOCK);
	SetCurrentDefaultClock(MASTER_CLOCK);
}

bool TimeManager::Update()
{
	return(mySystemClock->Update());
}

void TimeManager::CreateTimer(const Clocks aTimer)
{
	if(aTimer==SYSTEM_CLOCK) // Refactor away once we gain inheritance
	{
		if(mySystemClock!=NULL)
		{
			SAFE_DELETE(mySystemClock);
		}
		mySystemClock=new SystemTime();
		mySystemClock->Init();

	}
	else
	{
		if(myClocks[aTimer]!=NULL)
		{
			SAFE_DELETE(myClocks[aTimer]);
		}
		myClocks[aTimer]=new Timer(aTimer);
	}
}

bool TimeManager::AttachTimerToTimer(const Clocks aTimerToAttachTo,const Clocks aTimerToAttach)
{
	assert(myClocks[aTimerToAttach]!=NULL && aTimerToAttach!=SYSTEM_CLOCK);
	assert(myClocks[aTimerToAttachTo]!=NULL || (aTimerToAttachTo==SYSTEM_CLOCK));// Refactor away once we gain inheritance

	if(aTimerToAttachTo==SYSTEM_CLOCK)
	{
		mySystemClock->AttachTimer(myClocks[aTimerToAttach]);
	}
	else
	{
		myClocks[aTimerToAttachTo]->AttachTimer(myClocks[aTimerToAttach]);
	}

	return(true);
}

const Time& TimeManager::GetElapsedTime() const
{
	return(myClocks[myDefaultClock]->GetElapsedTime());
}

const Time& TimeManager::GetTotalTime() const
{
	return(myClocks[myDefaultClock]->GetTotalTime());
}

const Time& TimeManager::GetElapsedTime(const Clocks aTimer)  const
{
	assert((myClocks[aTimer]!=NULL) || (aTimer==SYSTEM_CLOCK));
	if(aTimer==SYSTEM_CLOCK) 
	{
		return(mySystemClock->GetElapsedTime());
	}
	else
	{
		return(myClocks[aTimer]->GetElapsedTime());
	}
}

const Time& TimeManager::GetTotalTime(const Clocks aTimer)  const
{
	assert((myClocks[aTimer]!=NULL) || (aTimer==SYSTEM_CLOCK));
	if(aTimer==SYSTEM_CLOCK) 
	{
		return(mySystemClock->GetTotalTime());
	}
	else
	{
		return(myClocks[aTimer]->GetTotalTime());
	}
}

void TimeManager::SetCurrentDefaultClock(const Clocks aTimer)
{
	myDefaultClock=aTimer;
}
		

bool TimeManager::SetClockPauseState(const Clocks aTimer,const bool aPauseState)
{
	assert(myClocks[aTimer]!=NULL);

	myClocks[aTimer]->SetPauseState(aPauseState);
	return(true);
}

void TimeManager::CreateInstance()
{
	myInstance = new TimeManager();

}

bool TimeManager::GetClockPauseState(const Clocks aTimer)
{
	return myClocks[aTimer]->GetPaused();
}


void TimeManager::ClearAllTimers(const Clocks aTimer)
{
	myClocks[aTimer]->ClearElapsedTime();
}