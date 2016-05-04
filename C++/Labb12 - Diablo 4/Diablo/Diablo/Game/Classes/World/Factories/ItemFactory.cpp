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
	const size_t RandomItemSlot = static_cast<size_t>(l1functions::math::GetRandomNumberSigned(static_cast<unsigned int>(myItemTemplates.size())));

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
	tmpItem.myPowerLevel = 1;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(6, enumItemTypes::eStats, 0, enumStatTypes::eStrength);
	tmpItem.itemNameAndDescription.name = "Headressyer Of Test";
	tmpItem.itemNameAndDescription.description = "Test Item 1 Description";
	tmpItem.myItemType = enumEquipTypes::eHead;
	tmpItem.myPowerLevel = 2;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(3, enumItemTypes::eStats, 0, enumStatTypes::eStrength);
	tmpItem.itemNameAndDescription.name = "Flotty hand of Mega test";
	tmpItem.itemNameAndDescription.description = "Test Item 2 Description";
	tmpItem.myItemType = enumEquipTypes::eHand;
	tmpItem.myPowerLevel = 1;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(6, enumItemTypes::eStats, 0, enumStatTypes::eStrength);
	tmpItem.itemNameAndDescription.name = "Flotty hand of Meta test";
	tmpItem.itemNameAndDescription.description = "Test Item 2 Description";
	tmpItem.myItemType = enumEquipTypes::eHand;
	tmpItem.myPowerLevel = 2;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(7, enumItemTypes::eStats, 0, enumStatTypes::eAgility);
	tmpItem.itemNameAndDescription.name = "Smelly boots of test";
	tmpItem.itemNameAndDescription.description = "Test Item 3 Description";
	tmpItem.myItemType = enumEquipTypes::eLegs;
	tmpItem.myPowerLevel = 1;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(14, enumItemTypes::eStats, 0, enumStatTypes::eAgility);
	tmpItem.itemNameAndDescription.name = "fasty boots of test";
	tmpItem.itemNameAndDescription.description = "Test Item 3 Description";
	tmpItem.myItemType = enumEquipTypes::eLegs;
	tmpItem.myPowerLevel = 2;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(2, enumItemTypes::eStats, 0, enumStatTypes::eKondition);
	tmpItem.itemNameAndDescription.name = "Rought milk carton of test";
	tmpItem.itemNameAndDescription.description = "Test Item 4 Description";
	tmpItem.myItemType = enumEquipTypes::eTorso;
	tmpItem.myPowerLevel = 1;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(4, enumItemTypes::eStats, 0, enumStatTypes::eKondition);
	tmpItem.itemNameAndDescription.name = "Rought cheese carton of test";
	tmpItem.itemNameAndDescription.description = "Test Item 4 Description";
	tmpItem.myItemType = enumEquipTypes::eTorso;
	tmpItem.myPowerLevel = 2;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(8, enumItemTypes::eStats, 0, enumStatTypes::eIntelligens);
	tmpItem.itemNameAndDescription.name = "Yellow pages of test";
	tmpItem.itemNameAndDescription.description = "Test Item 4 Description";
	tmpItem.myItemType = enumEquipTypes::eScroll;
	tmpItem.myPowerLevel = 1;
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(16, enumItemTypes::eStats, 0, enumStatTypes::eIntelligens);
	tmpItem.itemNameAndDescription.name = "Yellow pages of test";
	tmpItem.itemNameAndDescription.description = "Test Item 4 Description";
	tmpItem.myItemType = enumEquipTypes::eScroll;
	tmpItem.myPowerLevel = 2;
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