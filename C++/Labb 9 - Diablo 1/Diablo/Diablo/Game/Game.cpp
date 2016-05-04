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

	myRoomController.CreateRooms(25);
	
	myCurrentRoomIndex = l1functions::math::GetRandomNumberSigned(myRoomController.GetRoomCount());
	myRoomController.OnRoomEnterTrigger(myCurrentRoomIndex);

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



void Game::PlayerChangeRoom(const unsigned int aDoorInRoomIndex)
{
	TriggerNewTurn();
	myCurrentRoomIndex = myRoomController.ChangeRoom(myCurrentRoomIndex, GetCurrentRoom().GetADoorIndex(aDoorInRoomIndex));
}

void Game::PlayerPickUpItem(const unsigned int aItemToPickUp)
{
	myPlayer.AddItemToInventory(GetCurrentRoom().ItemPickedUp(aItemToPickUp));
}

void Game::BuildExplorerMenu(std::vector<enumMenuOptions>& aMenuHolderToBuild)
{
	aMenuHolderToBuild.push_back(enumMenuOptions::eChangeRoom);
	aMenuHolderToBuild.push_back(enumMenuOptions::eInventory);

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

		myRoomController.AddBuffsToRoom(tempCreature.GetBuffCount(), GetCurrentRoom().GetRoomIndex());
		myRoomController.AddItemsToRoom(tempCreature.GetItemCount(), GetCurrentRoom().GetRoomIndex());
		GetCurrentRoom().RemoveAllCreatures();
	}
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
	myPlayer.PrintPlayerInventory();
	
	system("pause");
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
	myRoomController.MakeVectorOfDoorNamesInRoom(currentRoomDoors ,myCurrentRoomIndex);

	unsigned int menuChoice = (l1functions::console::input::GivePlayerMenuOptionsWithBack(currentRoomDoors));

	if (menuChoice < currentRoomDoors.size() -1)
	{
		PlayerChangeRoom(menuChoice);
	}
}

