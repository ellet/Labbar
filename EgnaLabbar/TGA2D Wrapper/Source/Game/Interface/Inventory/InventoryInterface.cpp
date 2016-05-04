#include "stdafx.h"
#include "InventoryInterface.h"
#include "../../Inventory/Inventory.h"

InventoryInterface::InventoryInterface(Inventory *aInventory, int aNumberOfRows, int aNumberOfColums, 
	const Vector2f &aSlotsStartPosition, const Vector2f &aSlotsOffset)
{
	myInventoryObjects.Init(static_cast<unsigned short>(myNumberOfColums * myNumberOfRows));
	myInventory = aInventory;
	myNumberOfRows = aNumberOfRows;
	myNumberOfColums = aNumberOfColums;
	mySlotsStartPosition = aSlotsStartPosition;
	mySlotsOffset = aSlotsOffset;
	myInventory->SetInventoryInterface(this);
	myName = "InventoryInterface";
}


InventoryInterface::~InventoryInterface()
{
}

void InventoryInterface::Update(const float aDeltaTime)
{
	myInventory->Update(aDeltaTime);
}

void InventoryInterface::Draw()const
{
	InterfaceBase::Draw();
	for (unsigned short i = 0; i < myInventoryObjects.Size(); i++)
	{
		myInventoryObjects[i]->Draw();
	}

	if (myInventory->HasSelectedObject() == true)
	{
		myInventory->GetSelectedObjectSprite()->Draw();
	}
	
}

void InventoryInterface::UpdateInventoryPositions()
{
	myInventoryObjects = myInventory->GetAllInventoryObjects();
	unsigned short count = 0;
	for (int y = 0; y < myNumberOfColums; y++)
	{
		for (int x = 0; x < myNumberOfRows; x++)
		{
			if (myInventoryObjects.Size() > count)
			{
				myInventoryObjects[static_cast<unsigned short>(count)]->SetRenderPriority(1001.f);
				myInventoryObjects[static_cast<unsigned short>(count)]->SetPositionAndCollider(Vector2f(
					GetPosition().x - mySlotsStartPosition.x + mySlotsOffset.x * x, 
					GetPosition().y - mySlotsStartPosition.y + mySlotsOffset.y * y));
				count++;				
			}
			else
			{
				return;
			}
		}
	}
}