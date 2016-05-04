#pragma once
#include "Event.h"
#include <GrowingArray\GrowingArray.h>
#include "../../Object/Object.h"

class Inventory;

class OnClickEvent : public Event
{
public:
	OnClickEvent();
	OnClickEvent(Object* aObject, Inventory *aInventory);
	~OnClickEvent();
	void AddEvent(Event *aEvent);
	void OnMouseClickEvent() override;
	bool Update(const float aDeltaTime) override;
	Object* GetAObject();

	virtual void OnCombineWithObjectEvent(const std::string &aOtherObjectName) override;

private:
	CommonUtilities::GrowingArray<Event*> myActiveEvents;
	Inventory *myInventory;
};

