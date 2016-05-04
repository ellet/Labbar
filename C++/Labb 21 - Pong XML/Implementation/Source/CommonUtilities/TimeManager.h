#pragma once
#include <Windows.h>
#include "Timer.h"
#include <vector>

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Update();

	double GetDeltaTime() const;

	size_t CreateNewTimer();

	LONGLONG GetTimeSinceStart();

	Timer & GetTimer(size_t aTimerIndex);

	const Time * GetTimerTime(size_t aTimerIndex) const;

private:
	void UpdateAllTimers();
	void PauseAllTimers();
	void ResumeAllTimers();

	LARGE_INTEGER myFrequency;
	LARGE_INTEGER myStartStamp;
	LARGE_INTEGER myCurrentStamp;
	LARGE_INTEGER myPreviousStamp;
	LARGE_INTEGER myTimeDifference;

	LONGLONG myDeltaTime;

	std::vector<Timer> myTimers;
};

