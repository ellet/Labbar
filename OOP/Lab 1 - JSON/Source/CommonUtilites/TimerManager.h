#pragma once

#include "Timer.h"
#include <vector>
#include <windows.h>


namespace CommonUtilities
{
	typedef unsigned int TimerHandle;

	class TimerManager
	{
	public:
		TimerManager(void);
		~TimerManager(void);


		TimerHandle				CreateTimer();
		const Timer&			GetTimer(const TimerHandle aHandle) const;
		void					UpdateTimers();
		void					StartAllTimers();
		void					StopAllTimers();
		void					StartTimer(const TimerHandle aHandle);
		void					StopTimer(const TimerHandle aHandle);
		void					PrintTimers() const;

	private:
		std::vector<Timer>		myTimers;
		LARGE_INTEGER			myLastTime;
		double					myFrequence;

	};
}
namespace CU = CommonUtilities;