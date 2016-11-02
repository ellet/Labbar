#ifndef SYSTEMTIME_HEADER
#define SYSTEMTIME_HEADER

#include "Timer.h"
#include "windows.h"

namespace CommonUtilities
{
	class SystemTimer :
		public Timer
	{
	public:
		SystemTimer();
		~SystemTimer();

		void Init();
		bool Update();

	private:
		LARGE_INTEGER myPerformanceTimercalibrationData;
		LARGE_INTEGER myClockStarted;
		LARGE_INTEGER myFrameStarted;
		LARGE_INTEGER myCallOverhead;


	};
};

#endif