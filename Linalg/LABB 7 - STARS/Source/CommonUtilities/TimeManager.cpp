#include "TimeManager.h"


TimeManager::TimeManager()
{
	QueryPerformanceFrequency(&myFrequency);
	QueryPerformanceCounter(&myStartStamp);
	myPreviousStamp = myStartStamp;
	myCurrentStamp = myStartStamp;

	myFrequency.QuadPart /= 1000000;
}


TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&myCurrentStamp);
	myTimeDifference.QuadPart =  (myCurrentStamp.QuadPart - myStartStamp.QuadPart) / (myFrequency.QuadPart);
	myDeltaTime = (myCurrentStamp.QuadPart - myPreviousStamp.QuadPart) / (myFrequency.QuadPart);

	myPreviousStamp = myCurrentStamp;
	UpdateAllTimers();
}

double TimeManager::GetDeltaTime() const
{
	return static_cast<double>(myDeltaTime) / 1000000.0;
}

size_t TimeManager::CreateNewTimer()
{
	myTimers.push_back(Timer(myTimeDifference.QuadPart));
	return myTimers.size() - 1;
}

LONGLONG TimeManager::GetTimeSinceStart()
{
	return  (myTimeDifference.QuadPart) / 1000000;
}

Timer & TimeManager::GetTimer(size_t aTimerIndex)
{
	return myTimers[aTimerIndex];
}

const Time * TimeManager::GetTimerTime(size_t aTimerIndex) const
{
	return myTimers[aTimerIndex].GetTime();
}

void TimeManager::UpdateAllTimers()
{
	for (size_t iTimer = 0; iTimer < myTimers.size(); iTimer++)
	{
		myTimers[iTimer].Update(myTimeDifference.QuadPart);
	}
}

void TimeManager::PauseAllTimers()
{
	for (size_t iTimer = 0; iTimer < myTimers.size(); iTimer++)
	{
		myTimers[iTimer].PauseTimer();
	}
}

void TimeManager::ResumeAllTimers()
{
	for (size_t iTimer = 0; iTimer < myTimers.size(); iTimer++)
	{
		myTimers[iTimer].UnpauseTimer();
	}
}

