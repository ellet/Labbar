#pragma once
#include "Event.h"
#include <string>

class OnCombineEvent : public Event
{
public:
	OnCombineEvent(std::string &aObjectName);
	~OnCombineEvent();
	bool Update(const float aDeltaTime) override;
	void AddEvent(Event *aEvent);

	virtual void OnCombineWithObjectEvent(const std::string &aOtherObjectName) override;

private:
	std::string myNameToCombineWith;
	CommonUtilities::GrowingArray<Event*> myActiveEvents;
};