#pragma once
#include "Item.h"
#include <vector>

class Inventory
{
public:
	Inventory();
	~Inventory();

	void AddItem(const Item & aItemToAdd);

	void RecalculateInventoryStats();

	std::vector<Buff> & GetInventoryStats();

	void SetItemLimit(const unsigned int aMaxLimit);

	void PrintInventory() const;

private:
	std::vector<Item> myItems;

	unsigned int myMaxSize;

	std::vector<Buff> myStatsBuilder;
};