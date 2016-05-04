#include "stdafx.h"
#include "EventManager.h"
#include "Events\Event.h"

CommonUtilities::GrowingArray<Event*> EventManager::myActiveEvents;
EventManager *EventManager::ourInstance;

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
	myActiveEvents.DeleteAll();
}

void EventManager::Init()
{
	myActiveEvents.Init(20);
}

void EventManager::AddEvent(Event *aEvent)
{
	GetInstance().AddEventInternal(aEvent);
}

void EventManager::AddEventInternal(Event *aEvent)
{
	myActiveEvents.Add(aEvent);
}

void EventManager::UpdateAllEvents(const float aDeltaTime)
{
	GetInstance().UpdateAllEventsInternal(aDeltaTime);
}

void EventManager::UpdateAllEventsInternal(const float aDeltaTime)
{
	for (int i = static_cast<int>(myActiveEvents.Size()) - 1; i >= 0; i--)
	{
		if (myActiveEvents[static_cast<unsigned short>(i)]->Update(aDeltaTime) == false)
		{
			myActiveEvents.DeleteCyclicAtIndex(static_cast<unsigned short>(i));
		}
	}
}

void EventManager::RemoveAllEvents()
{
	GetInstance().RemoveAllEventsInternal();
}

void EventManager::RemoveAllEventsInternal()
{
	myActiveEvents.DeleteAll();
}

CommonUtilities::GrowingArray<Event*>& EventManager::GetAllEvents()
{
	return GetInstance().GetAllEventsInternal();
}

CommonUtilities::GrowingArray<Event*>& EventManager::GetAllEventsInternal()
{
	return myActiveEvents;
}
