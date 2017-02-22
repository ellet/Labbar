#pragma once
#include "Time\Stopwatch.h"
#include "Serialization\SerializeHeader.h"

struct ImportantMessageData
{
	unsigned short messageID;
	unsigned short targetID;
	SB::Stopwatch timerOutTimer;
	unsigned int timeStamp;
	StreamType myStream;
};
