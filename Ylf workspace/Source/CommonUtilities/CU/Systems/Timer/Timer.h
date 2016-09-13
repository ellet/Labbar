#pragma once
#include "Time.h"

namespace CommonUtilities
{

	class Timer
	{
	public:
		Timer();
		~Timer();

		void PauseTimer();

		void UnpauseTimer();

		const Time & GetTime();

		void Reset();

	private:
		void SetTime(LONGLONG aTimeStamp);

		LONGLONG myTimeStamp;
		LONGLONG myPauseStamp;

		Time myTime;

		bool myImPaused;
	};
}