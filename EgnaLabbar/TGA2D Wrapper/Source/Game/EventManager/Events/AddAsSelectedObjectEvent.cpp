#include "stdafx.h"
#include "AddAsSelectedObjectEvent.h"
#include "../../Inventory/Inventory.h"

AddAsSelectedObjectEvent::AddAsSelectedObjectEvent(Inventory *aInventory, Object *aObject)
{
	myInventory = aInventory;
	myObject = aObject;
}


AddAsSelectedObjectEvent::~AddAsSelectedObjectEvent()
{
}

void AddAsSelectedObjectEvent::OneShotEvent()
{
	myInventory->SetSelectedObject(myObject);
}
