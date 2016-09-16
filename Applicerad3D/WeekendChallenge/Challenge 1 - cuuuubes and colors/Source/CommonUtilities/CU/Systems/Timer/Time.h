#pragma once
#include "CU/Includes/WindowsDefines.h"


namespace CommonUtilities
{

	class Time
	{
	public:
		Time(LONGLONG aTime);
		~Time();

		LONGLONG GetMicroSeconds() const;

		float GetMilliSeconds() const;

		float GetMinutes() const;

		float GetHours() const;

		float GetSeconds() const;

		void SetTime(LONGLONG aTime);
	private:
		LONGLONG myTimeInMicroSeconds;
	};

}
