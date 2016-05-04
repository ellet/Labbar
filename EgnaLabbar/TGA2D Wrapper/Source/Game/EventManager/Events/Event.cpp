#include "stdafx.h"
#include "Event.h"


Event::Event()
{
	myName = "No Name Event";
	myIsActive = true;
}


Event::~Event()
{
}

std::string Event::GetName()
{
	return myName;
}

bool Event::Update(const float aDeltaTime)
{
	(aDeltaTime);
	return myIsActive;
}

void Event::OneShotEvent()
{
}

void Event::OnCombineWithObjectEvent(const std::string &aOtherObjectName)
{
	(aOtherObjectName);
}

void Event::OnMouseClickEvent()
{
}

void Event::OnUseEvent()
{
}

void Event::StartEvent()
{
	myIsActive = true;
}

void Event::StopEvent()
{
	myIsActive = false;
}

Object *Event::GetAObject()
{
	return myObject;
}

void Event::SetObject(Object *aObject)
{
	myObject = aObject;
}
