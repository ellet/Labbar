#pragma once
#include "Timer.h"
#include <vector>
#include "CU/Systems/DLDebug/DL_Debug.h"

struct TimeManagerTimeStamps;

namespace CommonUtilities
{

	class TimeManager
	{
	public:
		TimeManager();
		~TimeManager();

		void Update();

		const Time & GetDeltaTime();

		LONGLONG GetTimeSinceStart();

		LONGLONG GetMainStamp();

		const Time & GetTimerTime(size_t aTimerIndex);

		void PauseAllTimers();

		void ResumeAllTimers();

	private:

		void DoUpdate();

		void DoPauseAllTimers();
		void DoResumeAllTimers();

		double myFrequency;
		
		TimeManagerTimeStamps * myStamps;

		LONGLONG myDeltaTime;

		bool myImPaused;

		std::vector<Timer> myTimers;
	};

};
