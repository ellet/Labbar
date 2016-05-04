#pragma once
#include "Event.h"

class ShutdownEvent : public Event
{
public:

	ShutdownEvent();
	~ShutdownEvent();

	virtual void OneShotEvent() override;

};
