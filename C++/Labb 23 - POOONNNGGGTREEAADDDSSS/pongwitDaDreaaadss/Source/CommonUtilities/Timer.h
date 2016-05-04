#pragma once
#include "Time.h"

class Timer
{
public:
	Timer(LONGLONG aTimeStamp);
	~Timer();
	
	void PauseTimer();

	void UnpauseTimer();

	void Update(LONGLONG aTimeStamp);

	const Time* GetTime() const;

private:
	LONGLONG myTimeStamp;
	LONGLONG myPauseStamp;

	Time myTime;

	bool myImPaused;
	bool myUnpause;
};