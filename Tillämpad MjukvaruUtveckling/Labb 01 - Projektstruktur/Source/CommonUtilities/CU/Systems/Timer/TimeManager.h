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
		static void Create();
		static void Destroy();

		static void Update();

		static Time GetDeltaTime();

		//static size_t CreateNewTimer();

		static LONGLONG GetTimeSinceStart();

		static LONGLONG GetMainStamp();

		//static Timer & GetTimer(size_t aTimerIndex);

		static const Time & GetTimerTime(size_t aTimerIndex);

		static void PauseAllTimers();

		static void ResumeAllTimers();

	private:
		TimeManager();
		~TimeManager();

		void DoUpdate();

		static TimeManager* ourInstance;

		static TimeManager & GetInstance() 
		{ 
			DL_ASSERT(ourInstance != nullptr, "TimeManager instance is nullptr"); 
			return (*ourInstance);
		}

		void DoPauseAllTimers();
		void DoResumeAllTimers();

		double myFrequency;
		
		TimeManagerTimeStamps * myStamps;

		LONGLONG myDeltaTime;

		bool myImPaused;

		std::vector<Timer> myTimers;
	};

};
