#include "Timer.h"



Timer::Timer(LONGLONG aTimeStamp) : myTime(0)
{
	myTimeStamp = aTimeStamp;
	myPauseStamp = myTimeStamp;
	myImPaused = false;
	myUnpause = false;
}


Timer::~Timer()
{
}

void Timer::PauseTimer()
{
	myImPaused = true;
}

void Timer::UnpauseTimer()
{
	myUnpause = true;
}

void Timer::Update(LONGLONG aTimeStamp)
{
	if (myImPaused == false)
	{
		myTime.SetTime(aTimeStamp - myTimeStamp);
	}
	else if (myPauseStamp == myTimeStamp)
	{
		myPauseStamp = aTimeStamp;
	}
	else if (myUnpause == true)
	{
		myImPaused = false;
		myUnpause = false;

		myTimeStamp = aTimeStamp - (myPauseStamp - myTimeStamp);
	}
}

const Time * Timer::GetTime() const
{
	return &myTime;
}