#ifndef TIMEMANAGER_HEADER
#define TIMEMANAGER_HEADER

#include "DatatypeTime.h"
#include "GrowingArray.h"
//#include <vector>

namespace CommonUtilities
{
 	class Timer;
 	class SystemTimer;

	class TimeManager
	{
	public:
		TimeManager();
		~TimeManager();

		bool Update();

		void CreateTimer(const Clocks aTimer);
		bool AttachTimerToTimer(const Clocks aTimerToAttachTo,const Clocks aTimerToAttach);

		const Time& GetElapsedTime() const;
		const Time& GetTotalTime() const;

		const Time& GetElapsedTime(const Clocks aTimer) const;
		const Time& GetTotalTime(const Clocks aTimer) const;
		
		bool SetClockPauseState(const Clocks aTimer,const bool aPauseState);
		void SetCurrentDefaultClock(const Clocks aTimer);
		
	private:
		void InitDefaults();
		Clocks myDefaultClock;
		CommonUtilities::GrowingArray<Timer*> myTimers;
	};
};

#endif