#pragma once
#include "InterfaceBase.h"
#include "../EventManager/Events/Event.h"

class InterfaceClickable : public InterfaceBase, public Event
{
public:
	InterfaceClickable();
	~InterfaceClickable();
	void OnMouseClickEvent() override;
	void AddEvent(Event *aEvent);
private: 
	CommonUtilities::GrowingArray<Event*> myActiveEvents;
};

