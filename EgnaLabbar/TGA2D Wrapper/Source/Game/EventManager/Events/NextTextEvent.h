#pragma once
#include "Event.h"

class NextTextEvent : public Event
{
public:
	NextTextEvent();
	~NextTextEvent();

	virtual void OneShotEvent() override;

};