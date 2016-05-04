#include "stdafx.h"
#include "OnUseEvents.h"

OnUseEvents::OnUseEvents()
{
	myEvents.Init(20);
	myName = "OnUseEvent";
}


OnUseEvents::~OnUseEvents()
{
}

void OnUseEvents::AddEvent(Event *aEvent)
{
	myEvents.Add(aEvent);
}

void OnUseEvents::OnUseEvent()
{
	// Add functionallity when we need it
}

bool OnUseEvents::Update(const float aDeltaTime)
{
	for (int i = static_cast<int>(myEvents.Size()) - 1; i >= 0; i--)
	{
		if (myEvents[static_cast<unsigned short>(i)]->Update(aDeltaTime) == false)
		{
			myEvents.DeleteCyclicAtIndex(static_cast<unsigned short>(i));
		}
	}
	return myIsActive;
}