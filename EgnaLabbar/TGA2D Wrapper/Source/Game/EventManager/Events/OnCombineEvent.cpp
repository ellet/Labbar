#include "stdafx.h"
#include "OnCombineEvent.h"
#include <iostream>
#include "Event.h"

OnCombineEvent::OnCombineEvent(std::string &aObjectName)
{
	myActiveEvents.Init(20);
	myNameToCombineWith = aObjectName;
	Event::myIsActive = true;
	Event::myName = "On Combine Event";
}


OnCombineEvent::~OnCombineEvent()
{
	myActiveEvents.DeleteAll();
}

bool OnCombineEvent::Update(const float aDeltaTime)
{
	for (int i = static_cast<int>(myActiveEvents.Size()) - 1; i >= 0; i--)
	{
		if (myActiveEvents[static_cast<unsigned short>(i)]->Update(aDeltaTime) == false)
		{
			myActiveEvents.DeleteCyclicAtIndex(static_cast<unsigned short>(i));
		}
	}
	return myIsActive;
}

void OnCombineEvent::AddEvent(Event *aEvent)
{
	myActiveEvents.Add(aEvent);
}

void OnCombineEvent::OnCombineWithObjectEvent(const std::string &aOtherObjectName)
{
	std::cout << "OnCombineWithObjectEvent" << std::endl;
	if (myNameToCombineWith == aOtherObjectName)
	{
		for (unsigned short i = 0; i < myActiveEvents.Size(); i++)
		{
			myActiveEvents[i]->OneShotEvent();
		}
	}
}
