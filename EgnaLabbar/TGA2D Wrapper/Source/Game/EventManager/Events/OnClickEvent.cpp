#include "stdafx.h"
#include "OnClickEvent.h"
#include "../../Inventory/Inventory.h"
#include <InputWrapper/InputWrapper.h>

OnClickEvent::OnClickEvent()
{
	myActiveEvents.Init(20);
}

OnClickEvent::OnClickEvent(Object* aObject, Inventory *aInventory)
{
	myActiveEvents.Init(20);
	myObject = aObject;
	myName = "OnClickEvent";
	myInventory = aInventory;
}

OnClickEvent::~OnClickEvent()
{
}

void OnClickEvent::AddEvent(Event *aEvent)
{
	myActiveEvents.Add(aEvent);
}

void OnClickEvent::OnMouseClickEvent()
{

	//myInventory->SetSelectedObject(myObject); MOVE THIS TO ANOTHER PLACE! THEN REMOVE THE DEPENDENCY TO INVENTORY
	for (int i = 0; i < static_cast<int>(myActiveEvents.Size()); i++)
	{
		myActiveEvents[static_cast<unsigned short>(i)]->OneShotEvent();
	}
}

bool OnClickEvent::Update(const float aDeltaTime)
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

Object* OnClickEvent::GetAObject()
{
	return myObject;
}

void OnClickEvent::OnCombineWithObjectEvent(const std::string &aOtherObjectName)
{
	for (int i = static_cast<int>(myActiveEvents.Size()) - 1; i >= 0; i--)
	{
		myActiveEvents[static_cast<unsigned short>(i)]->OnCombineWithObjectEvent(aOtherObjectName);
	}
}
