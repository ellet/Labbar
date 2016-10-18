#ifndef TI_TIMER_HEADER
#define TI_TIMER_HEADER

#include "TI_Time.h"
#include "GrowingArray.h"

namespace TI_Time
{
	class Timer
	{
	public:
		Timer(Clocks aClock=MASTER_CLOCK);
		~Timer();

		void AttachTimer(Timer* aTimer);

		bool Update(Time& aElapsedTime);
		void SetPauseState(bool aPausedFlag);
		bool GetPaused(){return myIsPausedFlag;}

		const Time& GetTotalTime() const;
		const Time& GetElapsedTime() const;
		void ClearElapsedTime();
	private:
		bool myIsPausedFlag;
		CU::GrowingArray<Timer*> myAttachedTimers;
		Time myCurrentTime;
		Time myElapsedTime;
	};
};

#endif