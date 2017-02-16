#pragma once

#include "Time/Time.h"
#include <windows.h>

namespace SB
{
	class Stopwatch
	{
	public:
		Stopwatch();
		~Stopwatch();

		void Restart();

		Time GetElapsedTime() const;

	private:
		LONGLONG myStartTime;
		float myFrequency;
	};
}
