#pragma once

namespace CommonUtilities
{
	typedef unsigned int TimeUnit;

	class Time
	{
	public:
		Time(const TimeUnit someTime);
		~Time(void);

		TimeUnit			GetHours() const;
		TimeUnit			GetSeconds() const;
		TimeUnit			GetMinutes() const;
		TimeUnit			GetMilliseconds() const;
		TimeUnit			GetMicroseconds() const;


	private:
		TimeUnit			myTime;

	};

	inline TimeUnit Time::GetHours() const
	{
		return myTime / (6000000 * 60);
	}

	inline TimeUnit Time::GetMinutes() const
	{
		return myTime / 6000000;
	}

	inline TimeUnit Time::GetSeconds() const
	{
		return myTime / 1000000;
	}

	inline TimeUnit Time::GetMilliseconds() const
	{
		return myTime / 1000;
	}

	inline TimeUnit Time::GetMicroseconds() const
	{
		return myTime;
	}
}
namespace CU = CommonUtilities;