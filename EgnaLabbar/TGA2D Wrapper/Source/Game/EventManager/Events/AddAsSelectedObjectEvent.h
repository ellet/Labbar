#pragma once
#include "Event.h"
class Inventory;
class Object;
class AddAsSelectedObjectEvent : public Event
{
public:
	AddAsSelectedObjectEvent(Inventory *aInventory, Object *aObject);
	~AddAsSelectedObjectEvent();

	virtual void OneShotEvent() override;
private:
	Inventory *myInventory;
	Object *myObject;
};

