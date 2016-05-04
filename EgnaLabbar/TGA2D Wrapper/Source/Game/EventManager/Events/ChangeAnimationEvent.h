#pragma once
#include "Event.h"

class Object;

class ChangeAnimationEvent : public Event
{
public:
	ChangeAnimationEvent(const std::string & aAnimationToChangeTo, Object * const aObjectToChangeAnimationOn);
	~ChangeAnimationEvent();

	virtual void OneShotEvent() override;


private:
	std::string myAnimationToChangeTo;
	Object * myObjectToChangeAnimationOn;
};

