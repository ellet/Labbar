#include "stdafx.h"
#include "Chest.h"
#include "../HelpFunctions/HelpFunctions.h"
#include "../HelpFunctions/enumfunctions.h"
#include "Stats\BaseStatEnum.h"

Chest::Chest()
{
	myImOpen = false;
}


Chest::~Chest()
{
}

void Chest::AddItem(const Item & aItem)
{
	myItems.push_back(aItem);
}

bool Chest::ChestMenu(Player & aPlayer)
{
	if (myImOpen == false)
	{
		bool iHaveDoneTest;
		do
		{
			iHaveDoneTest = ImClosedMenu(aPlayer);
		} while (iHaveDoneTest == false);
	}

	if (myImOpen == true)
	{
		return ImOpenMenu(aPlayer);
	}
	return false;
}

bool Chest::ImClosedMenu(Player & aPlayer)
{
	l1functions::console::ClearScreen();
	l1functions::console::PrintToConsole("Chest is locked, how would you like to try to open it?");

	l1functions::console::ConsoleWhiteSpace();

	std::vector<std::string> itemsInChest;
	std::string tempChestOption;

	enumutility::GetStringFromEnum(enumChestOpeningOptions::eBruteForce, tempChestOption);
	itemsInChest.push_back(tempChestOption);
	enumutility::GetStringFromEnum(enumChestOpeningOptions::eLockPick, tempChestOption);
	itemsInChest.push_back(tempChestOption);

	unsigned int menuChoice = l1functions::console::input::GivePlayerMenuOptionsWithBack(itemsInChest);

	if (menuChoice >= myItems.size())
	{
		return true;
	}
	else
	{
		switch (static_cast<enumChestOpeningOptions>(menuChoice))
		{
		case enumChestOpeningOptions::eBruteForce:
			return StrengthTest(aPlayer);
			break;
		case enumChestOpeningOptions::eLockPick:
			return IntelligenceTest(aPlayer);
			break;

		default:
			l1functions::console::PrintErrorToConsole("Chest Menu Options out of range");
			return true;
		}
	}
}

bool Chest::ImOpenMenu(Player & aPlayer)
{
	if (IHaveItems() == false)
	{
		l1functions::console::PrintMessageWithPause("Chest is empty");
		return false;
	}
	else
	{

		l1functions::console::ClearScreen();
		l1functions::console::PrintToConsole("Choose a item.");

		l1functions::console::ConsoleWhiteSpace();

		std::vector<std::string> itemsInChest;
		MakeVectorOfItemNamesInChest(itemsInChest);

		unsigned int menuChoice = l1functions::console::input::GivePlayerMenuOptionsWithBack(itemsInChest);

		if (menuChoice < myItems.size())
		{
			aPlayer.AddItemToInventory(RemoveItem(menuChoice));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Chest::StrengthTest(Player & aPlayer)
{
	aPlayer.GetCreatureInPlayer().PayForAction();
	if (l1functions::math::RandomChanceHappend(aPlayer.GetCreatureInPlayer().GetStatValue(enumStatTypes::eStrength)))
	{
		l1functions::console::PrintMessageWithPause("Bruteforce succeded");
		myImOpen = true;
		return true;
	}
	else
	{
		l1functions::console::PrintMessageWithPause("Failed");
		return false;
	}
}

bool Chest::IntelligenceTest(Player & aPlayer)
{
	aPlayer.GetCreatureInPlayer().PayForAction();
	if (l1functions::math::RandomChanceHappend(aPlayer.GetCreatureInPlayer().GetStatValue(enumStatTypes::eIntelligens)), true)
	{
		l1functions::console::PrintMessageWithPause("Lockpick succeded");
		myImOpen = true;
		return true;
	}
	else
	{
		l1functions::console::PrintMessageWithPause("Failed");
		return false;
	}
}

bool Chest::IHaveItems()
{
	if (myItems.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Chest::MakeVectorOfItemNamesInChest(std::vector<std::string> & aStringVectorToFill) const
{
	for (unsigned int iItem = 0; iItem < myItems.size(); ++iItem)
	{
		aStringVectorToFill.push_back(myItems[iItem].itemNameAndDescription.name);
	}
}

Item Chest::RemoveItem(const unsigned int aItemInChestIndex)
{
	const Item tempItem = myItems[aItemInChestIndex];

	myItems.erase(myItems.begin() + aItemInChestIndex);

	return tempItem;
}
