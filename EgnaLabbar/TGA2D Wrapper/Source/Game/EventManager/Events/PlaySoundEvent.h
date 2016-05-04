#pragma once
#include "Event.h"
#include <string>
class PlaySoundEvent : public Event
{
public:
	PlaySoundEvent(const std::string &aSoundName, const bool aRepeat);
	~PlaySoundEvent();

	virtual void OneShotEvent() override;

private:
	std::string mySoundName;
	bool myRepeat;
};

