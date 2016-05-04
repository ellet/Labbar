#pragma once
#include "Event.h"
#include <GrowingArray\GrowingArray.h>

class OnUseEvents : public Event
{
public:
	OnUseEvents();
	~OnUseEvents();
	void AddEvent(Event *aEvent);
	virtual void OnUseEvent() override;
	virtual bool Update(const float aDeltaTime) override;
private:
	CommonUtilities::GrowingArray<Event*> myEvents;
};

