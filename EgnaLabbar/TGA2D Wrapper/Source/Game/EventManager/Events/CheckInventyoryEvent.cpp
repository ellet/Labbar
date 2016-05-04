#include "stdafx.h"
#include "CheckInventyoryEvent.h"
#include "../../Inventory/Inventory.h"
#include "../../Object/ObjectManager.h"

CheckInventoryEvent::CheckInventoryEvent(std::string &aObjectName, Inventory *aInventory)
{
	myObjectName = aObjectName;
	myInventory = aInventory;
	myActiveEvents.Init(5);
}


CheckInventoryEvent::~CheckInventoryEvent()
{
	myActiveEvents.DeleteAll();
}

void CheckInventoryEvent::AddEvent(Event *aEvent)
{
	myActiveEvents.Add(aEvent);
}

bool CheckInventoryEvent::Update(const float aDeltaTime)
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

void CheckInventoryEvent::OneShotEvent()
{
	if (myInventory->HasObject(myObjectName) == true)
	{
		for (int i = static_cast<int>(myActiveEvents.Size()) - 1; i >= 0; i--)
		{
			myActiveEvents[static_cast<unsigned short>(i)]->OneShotEvent();
		}
	}
}
