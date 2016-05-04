#pragma once
#include "Event.h"
#include <string>

class Inventory;
class Object;

class PickUpEvent :	public Event
{
public:
	PickUpEvent(Inventory *aInventory, const std::string &aObjectCallerName, const std::string &aObjectToAddName, bool aRemoveAfterAdd);
	~PickUpEvent();
	void OneShotEvent() override;
private:
	Inventory *myInventory;
	std::string myObjectToAdd;
	std::string myObjectCaller;
	bool myRemoveAfterAdd;
};

