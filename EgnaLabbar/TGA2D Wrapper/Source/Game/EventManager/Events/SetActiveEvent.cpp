#include "stdafx.h"
#include "SetActiveEvent.h"
#include "../../Object/ObjectManager.h"
#include "../../Object/Object.h"

SetActiveEvent::SetActiveEvent(const std::string &aObjectName, bool aValue)
{
	myObjectName = aObjectName;
	myValue = aValue;
}


SetActiveEvent::~SetActiveEvent()
{
}

void SetActiveEvent::OneShotEvent()
{
	ObjectManager::GetAObject(myObjectName)->SetIsActive(myValue);
}
