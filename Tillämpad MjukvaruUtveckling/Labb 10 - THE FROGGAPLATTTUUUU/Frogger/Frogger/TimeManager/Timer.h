#ifndef TIMER_HEADER
#define TIMER_HEADER

#include "DatatypeTime.h"
#include <vector>

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer(Clocks aClock=MASTER_CLOCK);
		virtual ~Timer();

		void AttachTimer(Timer* aTimer);
		bool Update(Time& aElapsedTime);
		virtual bool Update();
		void SetPauseState(bool aPausedFlag);

		const Time& GetTotalTime() const;
		const Time& GetElapsedTime() const;
	protected:
		Clocks myClockIdentity;
		bool myIsPausedFlag;
		Time myTotalTime;
		Time myTimeSinceLastUpdate;

		std::vector<Timer*> myAttachedTimers;
	};
};

#endif