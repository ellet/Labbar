#include "stdafx.h"
#include "ItemFactory.h"


ItemFactory::ItemFactory()
{
	CreateAllItems();
	CreateAllBuffs();
}


ItemFactory::~ItemFactory()
{
}

Item* ItemFactory::GetNewItem()
{
	return &myItemTemplates[0];
}

Buff * ItemFactory::GetNewBuff()
{
	return &myTempBuffTemplats[0];
}


void ItemFactory::CreateAllItems()
{
	Item tmpItem;

	tmpItem.itemBuff.Initialize(3, enumItemTypes::eStats, 0, enumStatTypes::eIntelligens);
	tmpItem.itemNameAndDescription.name = "Test Item 1";
	tmpItem.itemNameAndDescription.name = "Test Item 1 Description";
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(3, enumItemTypes::eStats, 0, enumStatTypes::eIntelligens);
	tmpItem.itemNameAndDescription.name = "Test Item 2";
	tmpItem.itemNameAndDescription.name = "Test Item 2 Description";
	myItemTemplates.push_back(tmpItem);
}

void ItemFactory::CreateAllBuffs()
{
	CreateAllTempBuffs();
}

void ItemFactory::CreateAllTempBuffs()
{
	Buff tempBuff;

	tempBuff.Initialize(3, enumItemTypes::eStats, 3, enumStatTypes::eIntelligens);
	myTempBuffTemplats.push_back(tempBuff);
}