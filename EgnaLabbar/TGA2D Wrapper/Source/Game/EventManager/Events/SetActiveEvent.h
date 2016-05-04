#pragma once
#include "Event.h"
#include <string>

class SetActiveEvent : public Event
{
public:
	SetActiveEvent(const std::string &aObjectName, bool aValue);
	~SetActiveEvent();

	virtual void OneShotEvent() override;
private:
	std::string myObjectName;
	bool myValue;
};

