#pragma once
#include "Item.h"
#include <vector>

class Inventory
{
public:
	Inventory();
	~Inventory();

	void AddItem(const Item* aItemToAdd);

	void RecalculateInventoryStats();

	std::vector<Buff> & GetInventoryStats();

	void SetItemLimit(const unsigned int aMaxLimit);

	void EquipedItemsPrintable(std::vector<std::string> & aStringVectorToAddTo) const;

	void PrintInventory(std::vector<std::string> & aStringVectorToAddTo) const;

	//const Item * GetItemRefrence(const size_t aItemIndex) const;

	void DropItem(const size_t aItemIndex, const Item* & aItem);

	void EquipItem(const size_t aItemIndex);

	void UnequipItem(const enumEquipTypes aSlotType);

	const size_t GetInventorySize() const;

	bool IHaveItems();

private:
	bool CheckIfAnyItemEquiped();

	void CreateEquipSlots();

	void RemoveItem(const size_t aItemIndex);

	std::vector<const Item*> myItems;

	std::vector<const Item*> myEquipedItems;

	unsigned int myMaxSize;

	std::vector<Buff> myStatsBuilder;
};