#pragma once
#include <GrowingArray\GrowingArray.h>

class Event;

class EventManager
{
public:
	inline static void Create();
	inline static void Destroy();
	static void Init();
	static void AddEvent(Event *aEvent);
	static void UpdateAllEvents(const float aDeltaTime);
	static void RemoveAllEvents();
	static CommonUtilities::GrowingArray<Event*>& GetAllEvents();
	static EventManager *ourInstance;
	inline static EventManager &GetInstance();
private:
	EventManager();
	~EventManager();
	void AddEventInternal(Event *aEvent);
	void UpdateAllEventsInternal(const float aDeltaTime);
	void RemoveAllEventsInternal();
	void InitInternal();
	static CommonUtilities::GrowingArray<Event*>& GetAllEventsInternal();
	static CommonUtilities::GrowingArray<Event*> myActiveEvents;
};


inline EventManager& EventManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "EventManager is nullptr");
	return (*ourInstance);
}

void EventManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new EventManager();
	}
}

void EventManager::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}