#pragma once
//#include <TimeManager.h>
//#include "../CommonUtilities/Timer/TimeManager.h"
#include "../CommonUtilities/Timer/Timer.h"
#include "../CommonUtilities/Timer/Alarm.h"
#include <vector>

class testTimmers
{
public:
	testTimmers();
	~testTimmers();

	void doTimerTest();

private:
	void DrawTimers();

	void AddTimer();



	//CommonUtilities::TimeManager myTimerManager;
	CommonUtilities::Timer myFirstTimer;
	CommonUtilities::Timer myDrawTimer;
	
	CommonUtilities::Timer myFPSTimer;

	CommonUtilities::Alarm myTestAlarm;

	bool myImPaused;

	std::vector<CommonUtilities::Timer> myTimmers;
};