#include "stdafx.h"
#include "Inventory.h"
#include "../../HelpFunctions/HelpFunctions.h"
#include "../../HelpFunctions/enumfunctions.h"

Inventory::Inventory()
{
	CreateEquipSlots();
}


Inventory::~Inventory()
{
}

void Inventory::AddItem(const Item* aItemToAdd)
{
	if (myMaxSize > myItems.size())
	{
		myItems.push_back(aItemToAdd);

		if ((myEquipedItems[static_cast<size_t>(aItemToAdd->myItemType)] == nullptr) || (myEquipedItems[static_cast<size_t>(aItemToAdd->myItemType)]->myPowerLevel < aItemToAdd->myPowerLevel))
		{
			EquipItem(myItems.size() - 1);
		}
	}
	else
	{
		l1functions::console::PrintMessageWithPause("Inventory is full");
	}
}

void Inventory::RecalculateInventoryStats()
{
	myStatsBuilder.clear();

	for (unsigned int iItem = 0; iItem < myEquipedItems.size(); ++iItem)
	{
		if (myEquipedItems[iItem] != nullptr && myEquipedItems[iItem]->itemBuff.GetBuffType() == enumItemTypes::eStats)
		{
			myStatsBuilder.push_back(myEquipedItems[iItem]->itemBuff);
		}
	}
}



const std::vector<Buff>& Inventory::GetInventoryStats() const
{
	return myStatsBuilder;
}

void Inventory::SetItemLimit(const unsigned int aMaxLimit)
{
	myMaxSize = aMaxLimit;
}

void Inventory::EquipedItemsPrintable(std::vector<std::string>& aStringVectorToAddTo) const
{
	for (unsigned int iItem = 0; iItem < myEquipedItems.size(); ++iItem)
	{
		if (myEquipedItems[iItem] != nullptr)
		{
			std::string tempString;
			enumutility::GetStringFromEnum(myEquipedItems[iItem]->myItemType, tempString);
			tempString += " slot has ";
			tempString += myEquipedItems[iItem]->itemNameAndDescription.name;
			tempString += " equiped";

			aStringVectorToAddTo.push_back(tempString);
		}
	}
}

void Inventory::PrintInventory(std::vector<std::string> & aStringVectorToAddTo) const
{
	for (unsigned int iItem = 0; iItem < myItems.size(); ++iItem)
	{
		aStringVectorToAddTo.push_back(myItems[iItem]->itemNameAndDescription.name);
	}
}

//const Item* Inventory::GetItemRefrence(const size_t aItemIndex) const
//{
//	return myItems[aItemIndex];
//}

void Inventory::MakeDifferencePrintable(const Item & aItem, std::string & aStringToBuild) const
{
	const Item & EquipedItem = (*myEquipedItems[static_cast<size_t>(aItem.myItemType)]);
	aStringToBuild = "Comparing: " + aItem.itemNameAndDescription.name + " and " + EquipedItem.itemNameAndDescription.name + "\n";

	if (aItem.itemBuff.GetStatType() == EquipedItem.itemBuff.GetStatType())
	{
		std::string tempString;
		enumutility::GetStringFromEnum(aItem.itemBuff.GetStatType(), tempString);

		aStringToBuild += "They share stat which is " + tempString + "\n";
		aStringToBuild += "Difference to stat bonus is " + l1functions::ConvertNumberToString(static_cast<int>(aItem.itemBuff.GetBuffValue()) - static_cast<int>(EquipedItem.itemBuff.GetBuffValue())) + "\n";
	}
	else
	{
		std::string tempString;
		enumutility::GetStringFromEnum(EquipedItem.itemBuff.GetStatType(), tempString);

		aStringToBuild += "Equiped item gives bonus to " + tempString + "\n";
		aStringToBuild += "With a stat bonus of " + l1functions::ConvertNumberToString(static_cast<int>(EquipedItem.itemBuff.GetBuffValue())) + "\n";


		enumutility::GetStringFromEnum(aItem.itemBuff.GetStatType(), tempString);
		aStringToBuild += "New item gives bonus to " + tempString + "\n";
		aStringToBuild += "With a stat bonus of " + l1functions::ConvertNumberToString(static_cast<int>(aItem.itemBuff.GetBuffValue())) + "\n";
	}
}

void Inventory::GetPrintableItemInformation(const Item & aItem, std::string & aStringToBuild) const
{
	std::string tempString;
	enumutility::GetStringFromEnum(aItem.itemBuff.GetStatType(), tempString);

	aStringToBuild = aItem.itemNameAndDescription.name + "\n";
	aStringToBuild += aItem.itemNameAndDescription.description + "\n";
	aStringToBuild += "Stat: " + tempString + "\n";
	aStringToBuild += "Power: " + l1functions::ConvertNumberToString(static_cast<int>(aItem.itemBuff.GetBuffValue()));
}

void Inventory::GetComparePrintable(const size_t aItemIndex, std::string & aStringToBuild) const
{
	MakeDifferencePrintable((*myItems[aItemIndex]), aStringToBuild);
}

void Inventory::GetItemPrintable(const size_t aItemIndex, std::string & aStringToBuild) const
{
	GetPrintableItemInformation((*myItems[aItemIndex]), aStringToBuild);
}

bool Inventory::CheckIfItemSlotEquiped(const size_t aItemIndex)
{
	const size_t ItemIndex = static_cast<size_t>(myItems[aItemIndex]->myItemType);
	if (myEquipedItems[ItemIndex] == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Inventory::DropItem(const size_t aItemIndex, const Item* & aItem)
{
	aItem = myItems[aItemIndex];

	RemoveItem(aItemIndex);
}

void Inventory::EquipItem(const size_t aItemIndex)
{
	const Item* ItemToEquip = myItems[aItemIndex];

	if (ItemToEquip->myItemType != enumEquipTypes::eNonEquip)
	{
		if (myEquipedItems[static_cast<size_t>(ItemToEquip->myItemType)] != nullptr)
		{
			myItems.push_back(myEquipedItems[static_cast<size_t>(ItemToEquip->myItemType)]);
		}

		myEquipedItems[static_cast<size_t>(ItemToEquip->myItemType)] = ItemToEquip;
		RemoveItem(aItemIndex);
	}
	else
	{
		l1functions::console::PrintMessageWithPause("Item is not equipable");
	}
}

void Inventory::UnequipItem(const enumEquipTypes aSlot)
{
	if (myEquipedItems[static_cast<size_t>(aSlot)] != nullptr)
	{
		AddItem(myEquipedItems[static_cast<size_t>(aSlot)]);
		myEquipedItems[static_cast<size_t>(aSlot)] = nullptr;
	}
}



const size_t Inventory::GetInventorySize() const
{
	return myItems.size();
}

bool Inventory::IHaveItems()
{
	if (myItems.size() > 0 || CheckIfAnyItemEquiped())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Inventory::CheckIfAnyItemEquiped()
{
	for (size_t iItem = 0; iItem < myEquipedItems.size(); ++iItem)
	{
		if (myEquipedItems[iItem] != nullptr)
		{
			return true;
		}
	}
	return false;
}

void Inventory::CreateEquipSlots()
{
	for (size_t iEquipSlot = 0; iEquipSlot < static_cast<size_t>(enumEquipTypes::eNonEquip); ++iEquipSlot)
	{
		myEquipedItems.push_back(nullptr);
	}
}

void Inventory::RemoveItem(const size_t aItemIndex)
{
	myItems.erase(myItems.begin() + aItemIndex);
}
