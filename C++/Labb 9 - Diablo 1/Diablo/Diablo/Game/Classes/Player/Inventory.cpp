#include "stdafx.h"
#include "Inventory.h"
#include "../../HelpFunctions/HelpFunctions.h"

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

void Inventory::AddItem(const Item & aItemToAdd)
{
	if (myMaxSize > myItems.size())
	{
		myItems.push_back(aItemToAdd);
	}
	else
	{
		l1functions::console::PrintMessageWithPause("Inventory is full");
	}
}

void Inventory::RecalculateInventoryStats()
{
	myStatsBuilder.clear();

	for (unsigned int iItem = 0; iItem < myItems.size(); ++iItem)
	{
		if (myItems[iItem].itemBuff.GetBuffType() == enumItemTypes::eStats)
		{
			myStatsBuilder.push_back(myItems[iItem].itemBuff);
		}
	}
}



std::vector<Buff>& Inventory::GetInventoryStats()
{
	return myStatsBuilder;
}

void Inventory::SetItemLimit(const unsigned int aMaxLimit)
{
	myMaxSize = aMaxLimit;
}

void Inventory::PrintInventory() const
{
	std::vector<std::string> itemNames;

	for (unsigned int iItem = 0; iItem < myItems.size(); ++iItem)
	{
		itemNames.push_back(myItems[iItem].itemNameAndDescription.name);
	}

	l1functions::console::PrintVectorOfStrings(itemNames);
}
