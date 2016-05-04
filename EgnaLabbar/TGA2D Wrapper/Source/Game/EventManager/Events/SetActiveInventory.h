#pragma once
#include "Event.h"
#include <string>

class SetActiveInterface : public Event
{
public:
	SetActiveInterface(std::string &aName, bool aValue);
	~SetActiveInterface();

	virtual void OneShotEvent() override;
private:
	std::string myName;
	bool myValue;
};

