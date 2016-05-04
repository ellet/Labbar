#pragma once
#include "Event.h"
#include <string>

class Inventory;

class CheckInventoryEvent : public Event
{
public:
	CheckInventoryEvent(std::string &aObjectName, Inventory *aInventory);
	~CheckInventoryEvent();
	void AddEvent(Event *aEvent);
	bool Update(const float aDeltaTime) override;
	virtual void OneShotEvent() override;
private:
	std::string myObjectName;
	Inventory *myInventory;
	CommonUtilities::GrowingArray<Event*> myActiveEvents;
};

