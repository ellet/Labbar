#include "stdafx.h"
#include "TimeManager.h"
#include "Timer.h"
#include "SystemTimer.h"
#include "assert.h"


namespace CommonUtilities
{
	TimeManager::TimeManager()
	{
		for(unsigned int counter = 0; counter < NUM_CLOCKS; counter++)
			myTimers.Add(NULL);
			
		 	
		SystemTimer* aSystemTimer = new SystemTimer();
		aSystemTimer->Init();
		myTimers[SYSTEM_CLOCK] = aSystemTimer;
		
		InitDefaults();
	}
	TimeManager::~TimeManager()
	{
		for(unsigned int counter = 0; counter < myTimers.Count(); counter++)
		{
			if(myTimers[counter]!=NULL)
			{
				delete(myTimers[counter]);
				myTimers[counter] = NULL;
			}
		}
	}

	void TimeManager::InitDefaults()
	{
		 CreateTimer(MASTER_CLOCK);
		 CreateTimer(GAME_CLOCK);
		 CreateTimer(GUI_CLOCK);
		 AttachTimerToTimer(SYSTEM_CLOCK,MASTER_CLOCK);
		 AttachTimerToTimer(MASTER_CLOCK,GAME_CLOCK);
		 AttachTimerToTimer(MASTER_CLOCK,GUI_CLOCK);
		 SetCurrentDefaultClock(GAME_CLOCK);
	}

	bool TimeManager::Update()
	{
		return(myTimers[SYSTEM_CLOCK]->Update());
	}

	 void TimeManager::CreateTimer(const Clocks aTimer)
	 {
	  	if(myTimers[aTimer]!=NULL)
	  	{
	  		delete(myTimers[aTimer]);
	  		myTimers[aTimer] = NULL;
	  	}
	  	myTimers[aTimer]=new Timer(aTimer);
	 	
	 }

	 bool TimeManager::AttachTimerToTimer(const Clocks aTimerToAttachTo,const Clocks aTimerToAttach)
	 {
	  	assert(myTimers[aTimerToAttach]!=NULL && aTimerToAttach!=SYSTEM_CLOCK);
	  	assert(myTimers[aTimerToAttachTo]!=NULL);
	  
	  	myTimers[aTimerToAttachTo]->AttachTimer(myTimers[aTimerToAttach]);
	 	return(true);
	 }

	 const Time& TimeManager::GetElapsedTime() const
	 {
	 	return(myTimers[myDefaultClock]->GetElapsedTime());
	 }
	 
	 const Time& TimeManager::GetTotalTime() const
	 {
	 	return(myTimers[myDefaultClock]->GetTotalTime());
	 }
	 
	 const Time& TimeManager::GetElapsedTime(const Clocks aTimer)  const
	 {
	 	assert((myTimers[aTimer]!=NULL) || (aTimer==SYSTEM_CLOCK));
	 	return(myTimers[aTimer]->GetElapsedTime());
	 }
	 
	 const Time& TimeManager::GetTotalTime(const Clocks aTimer)  const
	 {
	  	assert((myTimers[aTimer]!=NULL) || (aTimer==SYSTEM_CLOCK));
	  	return(myTimers[aTimer]->GetTotalTime());
	 }

	 void TimeManager::SetCurrentDefaultClock(const Clocks aTimer)
	 {
	 	myDefaultClock=aTimer;
	 }


	 bool TimeManager::SetClockPauseState(const Clocks aTimer,const bool aPauseState)
	 {
	 	assert(myTimers[aTimer]!=NULL);
	 
	  	myTimers[aTimer]->SetPauseState(aPauseState);
	  	return(true);
	 }

}
