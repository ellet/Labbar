#pragma once
#include "Event.h"
#include "../../Object/Object.h"
#include "PickUpEvent.h"
#include "ChangeLevelEvent.h"

class AutomaticInventoryAdderTest : public Event
{
public:
	AutomaticInventoryAdderTest();
	~AutomaticInventoryAdderTest();
	bool Update(const float aDeltaTime) override;
private:
	float myTimeElapsed;
	CommonUtilities::GrowingArray<Event*> myActiveEvents;
};

