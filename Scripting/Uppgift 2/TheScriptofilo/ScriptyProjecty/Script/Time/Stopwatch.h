#pragma once
#include <windows.h>
#include "Time.h"

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
