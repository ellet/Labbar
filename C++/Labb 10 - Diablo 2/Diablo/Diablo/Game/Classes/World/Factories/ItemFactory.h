#pragma once
#include "../../Player/Item.h"
#include "../../Stats/Buff.h"
#include <vector>

class ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();

	Item* GetNewItem();

	Buff* GetNewBuff();

private:
	void CreateAllBuffs();

	void CreateAllTempBuffs();

	void CreateAllItems();


	std::vector<Item> myItemTemplates;
	std::vector<Buff> myTempBuffTemplats;
};

