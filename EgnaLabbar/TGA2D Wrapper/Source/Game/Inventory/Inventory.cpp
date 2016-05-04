#include "stdafx.h"
#include "Inventory.h"
#include "../Object/Object.h"
#include "../Interface/Inventory/InventoryInterface.h"
#include <tga2d/sprite/sprite.h>
#include <Input/MouseInput/MouseInput.h>

Inventory::Inventory() : myMaxNumberOfObjects(4)
{
	myObjects.Init(static_cast<unsigned short>(myMaxNumberOfObjects));
	myObjectCount = 0;
	mySelectedObjectSprite = new Object();
	mySelectedObjectSprite->SetSprite(std::shared_ptr<DX2D::CSprite>(new DX2D::CSprite("Sprites/HighLight.dds")));
	mySelectedObjectData = mySelectedObjectSprite;
	mySelectedObjectSprite->SetRenderPriority(1010.f);
	mySelectedObjectSprite->SetIsActive(false);
}


Inventory::~Inventory()
{
	myObjects.DeleteAll();
	SAFE_DELETE(mySelectedObjectSprite);
}

bool Inventory::AddObjectToInventory(Object *aObject)
{
	unsigned short firstSize = myObjects.Size();
	if (myObjectCount + 1 <= myMaxNumberOfObjects)
	{
		myObjects.Add(new Object(*aObject));
		myObjectCount++;
		if (firstSize != myObjects.Size())
		{
			myInventoryInterface->UpdateInventoryPositions();
			return true;
		}
	}	
	return false;
}

const CommonUtilities::GrowingArray<Object*>& Inventory::GetAllInventoryObjects() const
{
	return myObjects;
}

Object* Inventory::GetAObject(Object * aObject)
{
	unsigned short index = myObjects.Find(aObject);
	if (index != CommonUtilities::GrowingArray<Object*>::FoundNone)
	{
		return myObjects[index];
	}
	else
	{
		return nullptr;
	}
}


void Inventory::RemoveObjectFromInventory(Object *aObjectToRemove)
{
	myObjects.DeleteCyclicAtIndex(static_cast<int>(myObjects.Find(aObjectToRemove)));
}

void Inventory::Update(const float aDeltaTime)
{
	for (unsigned short i = 0; i < myObjects.Size(); i++)
	{
		myObjects[i]->Update(aDeltaTime);
	}
}

void Inventory::SetInventoryInterface(InventoryInterface* aInterface)
{
	myInventoryInterface = aInterface;
}

void Inventory::SetSelectedObject(Object *aObject)
{
	for (unsigned short i = 0; i < myObjects.Size(); i++)
	{
		if (myObjects[i]->GetName() == aObject->GetName())
		{
			mySelectedObjectSprite->SetPosition(myObjects[i]->GetPosition());
			mySelectedObjectSprite->SetIsActive(true);
			mySelectedObjectData = aObject;
			MouseInput::SetMouseState(enumMouseStates::eHoldingItem);
		}
	}	
}

void Inventory::RemoveSelectedObject()
{
	mySelectedObjectSprite->SetIsActive(false);
}

bool Inventory::HasSelectedObject()
{
	return mySelectedObjectSprite->IsActive();
}

Object* Inventory::GetSelectedObject()
{
	return mySelectedObjectData;
}

Object * Inventory::GetSelectedObjectSprite()
{
	return mySelectedObjectSprite;
}

bool Inventory::HasObject(std::string &aName)
{
	for (unsigned short i = 0; i < myObjects.Size(); i++)
	{
		if (myObjects[i]->GetName() == aName)
		{
			return true;
		}
	}
	return false;
}
