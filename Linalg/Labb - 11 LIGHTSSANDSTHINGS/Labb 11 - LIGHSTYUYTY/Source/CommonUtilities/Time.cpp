#include "Time.h"



Time::Time(LONGLONG aTime)
{
	myTimeInMicroSeconds = aTime;
}


Time::~Time()
{
}



LONGLONG Time::GetMicroSeconds() const
{
	return myTimeInMicroSeconds;
}

int Time::GetMilliSeconds() const
{
	return static_cast<int>(myTimeInMicroSeconds / 1000);
}

int Time::GetMinutes() const
{
	return static_cast<int>(GetSeconds() / 60);
}

int Time::GetHours() const
{
	return static_cast<int>(GetMinutes() / 60);
}

int Time::GetSeconds() const
{
	return static_cast<int>(myTimeInMicroSeconds / 1000000);
}

void Time::SetTime(LONGLONG aTime)
{
	myTimeInMicroSeconds = aTime;
}

