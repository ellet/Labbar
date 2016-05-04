#pragma once
#include "../InterfaceBase.h"
#include "../../Object/Object.h"

class Inventory;

class InventoryInterface : public InterfaceBase
{
public:
	InventoryInterface(Inventory *aInventory, int aNumberOfRows, int aNumberOfColums, 
		const Vector2f &aSlotsStartPosition, const Vector2f &aSlotsOffset);
	~InventoryInterface();
	void Update(const float aDeltaTime) override;
	void Draw()const override;
	void UpdateInventoryPositions();
private:
	Inventory *myInventory;
	int myNumberOfRows;
	int myNumberOfColums;
	Vector2f mySlotsStartPosition;
	Vector2f mySlotsOffset;
	CommonUtilities::GrowingArray<Object*> myInventoryObjects;
};

