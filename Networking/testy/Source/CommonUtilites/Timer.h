#pragma once
#include "Time.h"

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		~Timer(void);

		void				AddTime(const TimeUnit aTime);
		void				Start();
		void				Stop();
		Time				GetLifeTime() const;
		Time				GetDeltaTime() const;
		TimeUnit			GetFPS() const;

	private:
		TimeUnit			myLifeTime;
		TimeUnit			myDeltaTime;
		bool				myOn;
	};

	inline void Timer::Start()
	{
		myOn = false;
	}

	inline void Timer::Stop()
	{
		myOn = true;
	}

	inline Time Timer::GetLifeTime() const
	{
		return Time(static_cast<TimeUnit>(myLifeTime));
	}

	inline Time Timer::GetDeltaTime() const
	{
		return Time(static_cast<TimeUnit>(myDeltaTime));
	}

	inline TimeUnit Timer::GetFPS() const
	{
		return 1000000 / myDeltaTime;
	}
}
namespace CU = CommonUtilities;