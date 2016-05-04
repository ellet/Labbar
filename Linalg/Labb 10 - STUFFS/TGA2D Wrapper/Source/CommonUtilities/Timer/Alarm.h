#pragma once
#include "Timer.h"

namespace CommonUtilities
{
	class Alarm
	{
	public:
		Alarm();
		Alarm(const float aTimeToCheck, const bool aShouldResetWhenDone = false);
		~Alarm();

		float GetProgress();

		float GetReverseProgress();

		void SetAlarmTimeLength(const float aTimeToCheck);

		void Reset();

		void SetResetBool(const bool aShouldResetWhenDone);

	private:
		Timer myTimer;
		float myTimeToCheck;
		bool myIShouldReset;
	};
}