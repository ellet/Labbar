#include "stdafx.h"
#include "ItemFactory.h"
#include "../../../HelpFunctions/HelpFunctions.h"


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
	const size_t RandomItemSlot = static_cast<size_t>(l1functions::math::GetRandomNumberSigned(static_cast<unsigned int>(myItemTemplates.size()-1)));

	return &myItemTemplates[RandomItemSlot];
}

Buff * ItemFactory::GetNewBuff()
{
	return &myTempBuffTemplats[0];
}


void ItemFactory::CreateAllItems()
{
	Item tmpItem;

	tmpItem.itemBuff.Initialize(3, enumItemTypes::eStats, 0, enumStatTypes::eIntelligens);
	tmpItem.itemNameAndDescription.name = "Headress Of Test";
	tmpItem.itemNameAndDescription.description = "Test Item 1 Description";
	tmpItem.myItemType = enumEquipTypes::eHead;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(3, enumItemTypes::eStats, 0, enumStatTypes::eStrength);
	tmpItem.itemNameAndDescription.name = "Flotty hand of Mega test";
	tmpItem.itemNameAndDescription.description = "Test Item 2 Description";
	tmpItem.myItemType = enumEquipTypes::eHand;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(7, enumItemTypes::eStats, 0, enumStatTypes::eAgility);
	tmpItem.itemNameAndDescription.name = "Smelly boots of test";
	tmpItem.itemNameAndDescription.description = "Test Item 3 Description";
	tmpItem.myItemType = enumEquipTypes::eLegs;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(2, enumItemTypes::eStats, 0, enumStatTypes::eKondition);
	tmpItem.itemNameAndDescription.name = "Rought milk carton of test";
	tmpItem.itemNameAndDescription.description = "Test Item 4 Description";
	tmpItem.myItemType = enumEquipTypes::eTorso;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(8, enumItemTypes::eStats, 0, enumStatTypes::eIntelligens);
	tmpItem.itemNameAndDescription.name = "Yellow pages of test";
	tmpItem.itemNameAndDescription.description = "Test Item 4 Description";
	tmpItem.myItemType = enumEquipTypes::eScroll;
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