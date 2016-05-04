#pragma once

#include "Event.h"
#include "../../Object/ElemenTypes.h"

class ActivateMagicElementEvent : public Event
{
public:
	ActivateMagicElementEvent(const eElementType aElementType);
	~ActivateMagicElementEvent();

	virtual void OneShotEvent() override;

protected:
	eElementType myElementType;
};

