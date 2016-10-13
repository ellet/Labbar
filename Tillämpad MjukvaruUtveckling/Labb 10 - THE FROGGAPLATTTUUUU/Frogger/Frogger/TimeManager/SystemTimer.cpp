#include "stdafx.h"
#include "SystemTimer.h"

using namespace CommonUtilities;


SystemTimer::SystemTimer()
{
	myClockIdentity = SYSTEM_CLOCK;
	myIsPausedFlag = false;
}

SystemTimer::~SystemTimer()
{
}

void SystemTimer::Init()
{
	myTotalTime.SetTime(0);
	myTotalTime.SetClock(myClockIdentity);
	myTimeSinceLastUpdate.SetTime(0);
	myTimeSinceLastUpdate.SetClock(myClockIdentity);
	

	myCallOverhead.QuadPart=0;
	for(int counter = 0; counter < 10000; counter++)
	{
		LARGE_INTEGER start,end;
		QueryPerformanceCounter(&start);
		QueryPerformanceCounter(&end);
		myCallOverhead.QuadPart=end.QuadPart-start.QuadPart;

	}
	myCallOverhead.QuadPart+=5000;
	myCallOverhead.QuadPart/=10000;


	QueryPerformanceFrequency(&myPerformanceTimercalibrationData);
	QueryPerformanceCounter(&myClockStarted);
	myFrameStarted=myClockStarted;
}


bool SystemTimer::Update()
{
	LARGE_INTEGER frameEnd;
	QueryPerformanceCounter(&frameEnd);
	myClockStarted.QuadPart+=myCallOverhead.QuadPart;

	double lastFrameTime=myTotalTime.GetTime();
	myTotalTime.SetTime(static_cast<double>((frameEnd.QuadPart-myClockStarted.QuadPart))/static_cast<double>(myPerformanceTimercalibrationData.QuadPart));
	myTimeSinceLastUpdate.SetTime(myTotalTime.GetTime()-lastFrameTime);
	
	for(unsigned int counter = 0; counter < myAttachedTimers.size(); counter++)
	{
		myAttachedTimers[counter]->Update(myTimeSinceLastUpdate);
	}
	QueryPerformanceCounter(&myFrameStarted);
	return(true);
}

	