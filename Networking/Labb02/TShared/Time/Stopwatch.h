#pragma once

#include "Time/Time.h"


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
