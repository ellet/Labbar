#include "stdafx.h"
#include "PickUpEvent.h"
#include "../../Inventory/Inventory.h"
#include "../../Object/Object.h"
#include <iostream>
#include "../../Object/ObjectManager.h"

PickUpEvent::PickUpEvent(Inventory *aInventory, const std::string &aObjectCallerName, const std::string &aObjectToAddName, bool aRemoveAfterAdd)
{
	myInventory = aInventory;
	myObjectToAdd = aObjectToAddName;
	myObjectCaller = aObjectCallerName;
	myName = "Pick Up Event";
	myRemoveAfterAdd = aRemoveAfterAdd;
}


PickUpEvent::~PickUpEvent()
{
}

void PickUpEvent::OneShotEvent()
{
	//std::cout << "OneShotEvent: Name: " << GetName() << std::endl;
	bool couldAdd = myInventory->AddObjectToInventory(ObjectManager::GetAObject(myObjectToAdd));
	if (couldAdd == false)
	{
		std::string message = "Could not add " + ObjectManager::GetAObject(myObjectToAdd)->GetName();
		std::cout << message << std::endl;
		DL_ASSERT(couldAdd, message.c_str());
	}
	else
	{
		std::string message = "Added the object";
		std::cout << message << std::endl;
		ObjectManager::GetAObject(myObjectCaller)->SetIsActive(!myRemoveAfterAdd);
	}
}
