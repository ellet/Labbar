#include "stdafx.h"
#include "TimerManager.h"
#include <assert.h>
#include <iostream>

namespace CommonUtilities
{
	TimerManager::TimerManager(void)
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);

		myFrequence = static_cast<double>(freq.QuadPart) / 1000000.0;

		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		myLastTime = time;
	}

	TimerManager::~TimerManager(void)
	{
	}

	void TimerManager::UpdateTimers()
	{
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		for (unsigned int i = 0; i < myTimers.size(); ++i)
		{
			myTimers[i].AddTime(static_cast<TimeUnit>((time.QuadPart - myLastTime.QuadPart) / myFrequence));
		}

		myLastTime = time;
	}

	void TimerManager::StartAllTimers()
	{
		for (unsigned int i = 0; i < myTimers.size(); ++i)
		{
			myTimers[i].Start();
		}
	}

	void TimerManager::StopAllTimers()
	{
		for (unsigned int i = 0; i < myTimers.size(); ++i)
		{
			myTimers[i].Stop();
		}
	}

	void TimerManager::StartTimer(const TimerHandle aHandle)
	{
		assert(aHandle < myTimers.size() && "StartTimer out of bounds!");
		myTimers[aHandle].Start();
	}

	void TimerManager::StopTimer(const TimerHandle aHandle)
	{
		assert(aHandle < myTimers.size() && "StopTimer out of bounds!");
		myTimers[aHandle].Stop();
	}

	const Timer& TimerManager::GetTimer(TimerHandle aHandle) const
	{
		assert(aHandle < myTimers.size() && "GetTimer out of bounds!");
		return myTimers[aHandle];
	}

	TimerHandle	TimerManager::CreateTimer()
	{
		myTimers.push_back(Timer());
		return myTimers.size() - 1;
	}

	void TimerManager::PrintTimers() const
	{
		system("cls");
		for (unsigned int i = 0; i < myTimers.size(); ++i)
		{
			const Time time = myTimers[i].GetLifeTime();
			std::cout << "Timer " << i << std::endl;
			std::cout << "Hours: " << time.GetHours() << std::endl;
			std::cout << "Minutes: " << time.GetMinutes() << std::endl;
			std::cout << "Seconds: " << time.GetSeconds() << std::endl;
			std::cout << "Milliseconds: " << time.GetMilliseconds() << std::endl;
			std::cout << "Microseconds: " << time.GetMicroseconds() << std::endl;
			std::cout << "FPS:" << myTimers[i].GetFPS() << std::endl;
			std::cout << "FrameTime:" << myTimers[i].GetDeltaTime().GetMilliseconds() << std::endl;
		}
	}
}