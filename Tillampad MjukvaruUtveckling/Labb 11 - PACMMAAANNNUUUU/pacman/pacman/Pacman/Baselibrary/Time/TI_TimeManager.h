#ifndef TI_TIMEMANAGER_HEADER
#define TI_TIMEMANAGER_HEADER

#include "TI_time.h"
#include "GrowingArray.h"

namespace TI_Time
{
	class Timer;
	class SystemTime;

	class TimeManager
	{
	public:
		static TimeManager *GetInstance(){return myInstance;}
		static void CreateInstance();
	
		void InitDefaults();

		bool Update();

		void CreateTimer(const Clocks aTimer);
		bool AttachTimerToTimer(const Clocks aTimerToAttachTo,const Clocks aTimerToAttach);

		const Time& GetElapsedTime() const;
		const Time& GetTotalTime() const;

		const Time& GetElapsedTime(const Clocks aTimer) const;
		const Time& GetTotalTime(const Clocks aTimer) const;
		bool SetClockPauseState(const Clocks aTimer,const bool aPauseState);

		void SetCurrentDefaultClock(const Clocks aTimer);
		bool GetClockPauseState(const Clocks aTimer);
		void ClearAllTimers(const Clocks aTimer);
		
	private:
		TimeManager();
		~TimeManager();
		Clocks myDefaultClock;
		CU::GrowingArray<Timer*> myClocks;
		SystemTime* mySystemClock;
		static TimeManager *myInstance;
	};
};
namespace TI = TI_Time;
#endif
