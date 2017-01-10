#pragma once

namespace SB
{

	struct PlaySoundEvent
	{
		PlaySoundEvent(const char * aSoundEventName) : mySoundEventName(aSoundEventName)
		{}

		const char * mySoundEventName;
	};

}
