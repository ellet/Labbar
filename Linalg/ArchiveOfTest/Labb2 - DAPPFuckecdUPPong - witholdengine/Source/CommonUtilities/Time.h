#pragma once
#include <windows.h>
class Time
{
public:
	Time(LONGLONG aTime);
	~Time();

	LONGLONG GetMicroSeconds() const;

	int GetMilliSeconds() const;

	int GetMinutes() const;

	int GetHours() const;

	int GetSeconds() const;

	void SetTime(LONGLONG aTime);
private:
	LONGLONG myTimeInMicroSeconds;
};

