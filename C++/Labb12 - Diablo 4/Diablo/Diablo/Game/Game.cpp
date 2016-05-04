#include "stdafx.h"
#include "Game.h"
#include "HelpFunctions/HelpFunctions.h"
#include <vector>
#include "Structs\name_and_description.h"
#include "HelpFunctions\CombatFunctions.h"
#include "Classes\Creature.h"
#include "HelpFunctions\enumfunctions.h"

Game::Game()
{
	myRunGame = true;
	myCurrentRoomIndex = 0;

	myTurnCount = 0;
	
	NameAndDescription temp;
	temp.name = "Player";
	temp.description = "Playery";

	myPlayer.GetCreatureInPlayer().SetName(temp);
}


Game::~Game()
{
}


void Game::RunGame()
{

	myRoomController.CreateRooms();
	
	myCurrentRoomIndex = l1functions::math::GetRandomNumberSigned(myRoomController.GetRoomCount());
	myRoomController.OnRoomEnterTrigger(&GetCurrentRoom());

	l1functions::console::PrintMessageWithPause("We are the collective, we are strong we will grow.");

	do
	{
		PlayerEnterCombat();

		if (PlayerFailCheck() == false)
		{
			CheckRoomForBuffs();

			ExploreMenu();
		}

	} while (myRunGame == true);
}












void Game::CheckRoomForBuffs()
{
	while (GetCurrentRoom().IHaveBuffs() == true)
	{
		l1functions::console::ClearScreen();
		l1functions::console::PrintToConsole("I found a buff!");
		myPlayer.GetCreatureInPlayer().AddTempBuff(GetCurrentRoom().BuffPickedUp());
			
		l1functions::console::ConsoleWhiteSpace();
		system("pause");
	}
}

void Game::TriggerNewTurn()
{
	l1functions::console::ClearScreen();
	myPlayer.GetCreatureInPlayer().PayForAction();
	++myTurnCount;

	myPlayer.GetCreatureInPlayer().RoundCheckTrigger(myTurnCount);
}

bool Game::PlayerFailCheck()
{

	if (myPlayer.GetCreatureInPlayer().GetHasEnergy() == false)
	{
		l1functions::console::PrintToConsole("YOU DIED OF EXHAUSTION!");

		system("pause");
		EndGame();

		return true;
	}
	else if (myPlayer.GetCreatureInPlayer().GetIsAlive(false) == false)
	{
		l1functions::console::PrintToConsole("YOU DIED!");

		system("pause");
		EndGame();

		return true;
	}
	else
	{
		return false;
	}

}

void Game::EndGame()
{
	myRunGame = false;
}

Room & Game::GetCurrentRoom()
{
	return myRoomController.AccessRoom(myCurrentRoomIndex);
}

void Game::ExploreMenu()
{


	GiveCurrentRoomDescription();

	l1functions::console::ConsoleWhiteSpace();

	std::vector<enumMenuOptions> menuOptions;
	BuildExplorerMenu(menuOptions);

	std::vector<std::string> menuOptionsToList;
	enumutility::CreateStringVectorFromEnumVector(menuOptions, menuOptionsToList);

	unsigned int userChoice = l1functions::console::input::GivePlayerMenuOptions(menuOptionsToList);
	TriggerMenuOption(menuOptions[userChoice]);
}

void Game::GiveCurrentRoomDescription()
{
	l1functions::console::ClearScreen();

	l1functions::console::PrintToConsole(GetCurrentRoom().GetRoomName());

	l1functions::console::ConsoleWhiteSpace();

	l1functions::console::PrintToConsole("This world has been collected");

	l1functions::console::ConsoleWhiteSpace();

	l1functions::console::PrintToConsole(GetCurrentRoom().GetRoomDescription());
}



void Game::PlayerChangeRoom(const size_t aDoorInRoomIndex)
{
	TriggerNewTurn();
	myCurrentRoomIndex = (*myRoomController.ChangeRoom(myCurrentRoomIndex, GetCurrentRoom().GetADoorIndex(aDoorInRoomIndex))).GetRoomIndex();
}

void Game::PlayerPickUpItem(const unsigned int aItemToPickUp)
{
	myPlayer.AddItemToInventory(GetCurrentRoom().ItemPickedUp(aItemToPickUp));
}

void Game::BuildInventoryOptionsMenu(std::vector<enumInventoryOptions> & aMenuHolderToBuild)
{
	aMenuHolderToBuild.push_back(enumInventoryOptions::eCheck);
	aMenuHolderToBuild.push_back(enumInventoryOptions::eEquip);
	aMenuHolderToBuild.push_back(enumInventoryOptions::eUnequip);
	aMenuHolderToBuild.push_back(enumInventoryOptions::eDrop);
}

void Game::BuildExplorerMenu(std::vector<enumMenuOptions>& aMenuHolderToBuild)
{
	aMenuHolderToBuild.push_back(enumMenuOptions::eChangeRoom);
	
	if (myPlayer.IHaveItemsInInventory() == true)
	{
		aMenuHolderToBuild.push_back(enumMenuOptions::eInventory);
	}

	if (myPlayer.IHaveSpellsInSpellBook() == true)
	{
		aMenuHolderToBuild.push_back(enumMenuOptions::eSpellBok);
	}

	if (GetCurrentRoom().IHaveItems() == true)
	{
		aMenuHolderToBuild.push_back(enumMenuOptions::eItems);
	}

	if (GetCurrentRoom().IHaveChests() == true)
	{
		aMenuHolderToBuild.push_back(enumMenuOptions::eChests);
	}

	aMenuHolderToBuild.push_back(enumMenuOptions::eStats);
	aMenuHolderToBuild.push_back(enumMenuOptions::eExit);
}

void Game::TriggerMenuOption(const enumMenuOptions aUserInput)
{
	l1functions::console::ClearScreen();
	switch (aUserInput)
	{

	case enumMenuOptions::eInventory:
		ShowInventory();
		break;

	case enumMenuOptions::eSpellBok:
		ShowSpellBook();
		break;

	case enumMenuOptions::eChangeRoom:
		GiveDoorChoiceOptions();
		break;

	case enumMenuOptions::eStats:
		PlayerCheckStats();
		break;

	case enumMenuOptions::eExit:
		EndGame();
		break;

	case enumMenuOptions::eItems:
		GivePickUpItemsOptions();
		break;

	case enumMenuOptions::eChests:
		GiveChestOptions();
		break;

	default:
		l1functions::console::PrintErrorToConsole("Main out of range");
		break;
	}
}

void Game::PlayerEnterCombat()
{
	if (GetCurrentRoom().IHaveCreatures() == true)
	{
		Creature tempCreature = GetCurrentRoom().GetCreatureInRoom();
		combat::Combat(myPlayer.GetCreatureInPlayer(), tempCreature);

		myRoomController.AccessRoomFactory().AddBuffsToRoom(tempCreature.GetBuffCount(), &GetCurrentRoom());
		myRoomController.AccessRoomFactory().AddItemsToRoom(tempCreature.GetItemCount(), &GetCurrentRoom());
		GetCurrentRoom().RemoveAllCreatures();
	}
}

std::vector<std::vector<std::string>> Game::GetCurrentRoomConnectionsNames()
{
	return std::vector<std::vector<std::string>>();
}

void Game::PlayerCheckStats()
{
	myPlayer.GetCreatureInPlayer().PrintCreatureStats();

	l1functions::console::ConsoleWhiteSpace();

	myPlayer.GetCreatureInPlayer().PrintCreatureVitals();

	l1functions::console::ConsoleWhiteSpace();

	std::vector<std::string> tempPlayerAttack;

	myPlayer.GetCreatureInPlayer().ConstructVectorOfNamesOfAttack(tempPlayerAttack);

	l1functions::console::PrintVectorOfStrings(tempPlayerAttack);

	system("pause");
}




void Game::ShowInventory()
{
	std::vector<std::string> ItemsInInventoryNames;

	myPlayer.PrintPlayerInventory(ItemsInInventoryNames);
	
	l1functions::console::PrintVectorOfStrings(ItemsInInventoryNames);

	l1functions::console::PrintToConsole("what would you like to do?");

	l1functions::console::ConsoleWhiteSpace();

	std::vector<enumInventoryOptions> inventoryOptions;
	BuildInventoryOptionsMenu(inventoryOptions);

	std::vector<std::string> inventoryOptionsText;
	enumutility::CreateStringVectorFromEnumVector(inventoryOptions, inventoryOptionsText);

	const size_t menuChoice = l1functions::console::input::GivePlayerMenuOptionsWithBack(inventoryOptionsText);

	if (menuChoice < inventoryOptionsText.size() - 1)
	{
		switch (inventoryOptions[menuChoice])
		{
			case enumInventoryOptions::eCheck:
				GiveItemCheckOptions();
				break;
			case enumInventoryOptions::eDrop:
				GiveDropItemOptions();
				break;
			case enumInventoryOptions::eEquip:
				GiveEquipItemOptions();
				break;
			case enumInventoryOptions::eUnequip:
				GiveUnequipItemOptions();
				break;
			default:
				l1functions::console::PrintErrorToConsole("Inventory option selection is out of range!");
				break;
		}
	}
}

void Game::ShowSpellBook()
{
	l1functions::console::ClearScreen();

	std::vector<std::string> spellNames;
	myPlayer.GetSpellsPrintableFromSpellBook(spellNames);

	l1functions::console::PrintVectorOfStrings(spellNames);

	l1functions::console::ConsoleWhiteSpace();

	l1functions::console::PrintToConsole("What would you like to do?");

	std::vector<std::string> tempMenu;
	tempMenu.push_back("Activate buffs");

	const size_t MenuChoice = l1functions::console::input::GivePlayerMenuOptionsWithBack(tempMenu);

	if (MenuChoice == 0)
	{
		GiveActivateSpellOptions();
	}
}

void Game::GiveActivateSpellOptions()
{
	do
	{
		const size_t SpellToActivate = ChooseSpellInSpellBook();

		if (SpellToActivate < myPlayer.GetSpellBookSize())
		{
			myPlayer.ActivateBuff(SpellToActivate);
		}
		else
		{
			break;
		}

	} while (myPlayer.IHaveSpellsInSpellBook() == true);

	if (myPlayer.IHaveSpellsInSpellBook() == false)
	{
		l1functions::console::PrintMessageWithPause("You have used all the spells in your spell book");
	}
}

void Game::GiveDropItemOptions()
{
	bool keepDroppingItems = true;
	do
	{
		const size_t ItemToDrop = ChooseItemInInventory();

		if (ItemToDrop < myPlayer.GetInventorySize())
		{
			const Item* itemToDrop = nullptr;
			myPlayer.DropItemInInventory(ItemToDrop, itemToDrop);

			GetCurrentRoom().AddItem(itemToDrop);
		}
		else
		{
			keepDroppingItems = false;
		}

	} while (keepDroppingItems);
}

void Game::GiveEquipItemOptions()
{
	bool keepEqupingItems = true;
	do
	{
		std::vector<std::string> equiptItemsNames;
		myPlayer.GetEquipedPrintableFromInventory(equiptItemsNames);

		l1functions::console::PrintVectorOfStrings(equiptItemsNames);
		
		l1functions::console::ConsoleWhiteSpace();

		const size_t ItemToEquip = ChooseItemInInventory();

		if (ItemToEquip < myPlayer.GetInventorySize())
		{
			if (myPlayer.CheckIfItemInInventoryEquipConflict(ItemToEquip))
			{
				std::string compareString;

				myPlayer.GetCompareString(ItemToEquip, compareString);

				l1functions::console::PrintMessageWithPause(compareString);

				if (l1functions::console::input::GetTrueOrFalseFromUser("Would you like to equip this?", true) == true)
				{
					myPlayer.EquipItemInInventory(ItemToEquip);
				}
			}
			else
			{
				myPlayer.EquipItemInInventory(ItemToEquip);
			}
		}
		else
		{
			keepEqupingItems = false;
		}

	} while (keepEqupingItems);
}

void Game::GiveUnequipItemOptions()
{
	bool keepUnequpingItems = true;
	do
	{
		std::vector<std::string> unequiptItemsNames;
		
		std::string tempString;
		std::string otherTempString;
		std::vector<enumEquipTypes> itemSlot;
		
		tempString = "Drop ";
		enumutility::GetStringFromEnum(enumEquipTypes::eHead, otherTempString);
		itemSlot.push_back(enumEquipTypes::eHead);
		tempString += otherTempString;
		unequiptItemsNames.push_back(tempString);

		tempString = "Drop ";
		enumutility::GetStringFromEnum(enumEquipTypes::eTorso, otherTempString);
		itemSlot.push_back(enumEquipTypes::eTorso);
		tempString += otherTempString;
		unequiptItemsNames.push_back(tempString);

		tempString = "Drop ";
		enumutility::GetStringFromEnum(enumEquipTypes::eHand, otherTempString);
		itemSlot.push_back(enumEquipTypes::eHand);
		tempString += otherTempString;
		unequiptItemsNames.push_back(tempString);

		tempString = "Drop ";
		enumutility::GetStringFromEnum(enumEquipTypes::eLegs, otherTempString);
		itemSlot.push_back(enumEquipTypes::eLegs);
		tempString += otherTempString;
		unequiptItemsNames.push_back(tempString);

		const size_t ItemToUnequip = l1functions::console::input::GivePlayerMenuOptionsWithBack(unequiptItemsNames);

		if (ItemToUnequip < unequiptItemsNames.size() - 1)
		{
			myPlayer.UnequipItemInInventory(itemSlot[ItemToUnequip]);
		}
		else
		{
			keepUnequpingItems = false;
		}

	} while (keepUnequpingItems);

}

void Game::GiveItemCheckOptions()
{
	bool keepShowingItems = true;
	do
	{
		std::vector<std::string> equiptItemsNames;
		myPlayer.GetEquipedPrintableFromInventory(equiptItemsNames);

		l1functions::console::PrintVectorOfStrings(equiptItemsNames);

		l1functions::console::ConsoleWhiteSpace();

		const size_t ItemToCheck = ChooseItemInInventory();

		if (ItemToCheck < myPlayer.GetInventorySize())
		{
			std::string aCheckItemString;
			myPlayer.GetItemInInventoryInformation(ItemToCheck, aCheckItemString);
			l1functions::console::PrintMessageWithPause(aCheckItemString);
		}
		else
		{
			keepShowingItems = false;
		}

	} while (keepShowingItems);
}


const size_t Game::ChooseItemInInventory()
{
	//l1functions::console::ClearScreen();
	l1functions::console::PrintToConsole("Choose an item");

	l1functions::console::ConsoleWhiteSpace();

	std::vector<std::string> ItemsInInventoryNames;
	myPlayer.PrintPlayerInventory(ItemsInInventoryNames);

	unsigned int menuChoice = l1functions::console::input::GivePlayerMenuOptionsWithBack(ItemsInInventoryNames);

	if (menuChoice >= ItemsInInventoryNames.size() - 1)
	{
		return ItemsInInventoryNames.size();
	}
	else
	{
		return menuChoice;
	}
	
}

const size_t Game::ChooseSpellInSpellBook()
{
	//l1functions::console::ClearScreen();
	l1functions::console::PrintToConsole("Choose a spell");

	l1functions::console::ConsoleWhiteSpace();

	std::vector<std::string> ItemsInInventoryNames;
	myPlayer.GetSpellsPrintableFromSpellBook(ItemsInInventoryNames);

	unsigned int menuChoice = l1functions::console::input::GivePlayerMenuOptionsWithBack(ItemsInInventoryNames);

	if (menuChoice >= ItemsInInventoryNames.size() - 1)
	{
		return ItemsInInventoryNames.size();
	}
	else
	{
		return menuChoice;
	}

}

void Game::GiveChestOptions()
{
	bool continueCheckingChest;
	do
	{
		continueCheckingChest = GetCurrentRoom().GetChestInRoom().ChestMenu(myPlayer);
	} while (continueCheckingChest);
	
}

void Game::GivePickUpItemsOptions()
{
	do
	{

		l1functions::console::ClearScreen();
		l1functions::console::PrintToConsole("Choose a item.");

		l1functions::console::ConsoleWhiteSpace();

		std::vector<std::string> itemsInRoom;
		myRoomController.MakeVectorOfItemNamesInRoom(itemsInRoom, myCurrentRoomIndex);

		unsigned int menuChoice = l1functions::console::input::GivePlayerMenuOptionsWithBack(itemsInRoom);
		
		if (menuChoice >= itemsInRoom.size() -1)
		{
			break;
		}
		else
		{
			PlayerPickUpItem(menuChoice);
		}
	} while (GetCurrentRoom().IHaveItems() == true);
}

void Game::GiveDoorChoiceOptions()
{
	l1functions::console::ClearScreen();
	l1functions::console::PrintToConsole("Choose a door.");

	l1functions::console::ConsoleWhiteSpace();

	std::vector<std::string> currentRoomDoors;
	myRoomController.MakeVectorOfDoorNamesInRoom(currentRoomDoors , GetCurrentRoom());

	unsigned int menuChoice = (l1functions::console::input::GivePlayerMenuOptionsWithBack(currentRoomDoors));

	if (menuChoice < currentRoomDoors.size() -1)
	{
		PlayerChangeRoom(menuChoice);
	}
}

