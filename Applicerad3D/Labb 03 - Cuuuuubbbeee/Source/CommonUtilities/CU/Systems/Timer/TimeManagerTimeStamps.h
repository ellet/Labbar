#pragma once
#include "windows.h"

struct TimeManagerTimeStamps 
{
	LARGE_INTEGER myStartStamp;
	LARGE_INTEGER myPauseStamp;
	LARGE_INTEGER myCountFromStamp;
	LARGE_INTEGER myCurrentStamp;
	LARGE_INTEGER myPreviousStamp;
	LARGE_INTEGER myTimeDifference;
};
