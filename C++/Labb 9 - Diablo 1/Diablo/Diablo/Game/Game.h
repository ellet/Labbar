#pragma once
#include "Classes\Creature.h"
#include "Classes\World\RoomController.h"
#include "Classes\Player.h"
#include "Classes\Menu\MenuOptionsEnum.h"


class Game
{
public:
	Game();
	~Game();

	void RunGame();

	

private:
	void CheckRoomForBuffs();

	void TriggerNewTurn();

	bool PlayerFailCheck();

	void EndGame();

	Room & GetCurrentRoom();

	void ExploreMenu();

	void GiveCurrentRoomDescription();

	void PlayerChangeRoom(const unsigned int aDoorInRoomIndex);

	void PlayerPickUpItem(const unsigned int aItemToPickUp);

	void BuildExplorerMenu(std::vector<enumMenuOptions> & aMenuHolderToBuild);

	void TriggerMenuOption(enumMenuOptions);

	void PlayerEnterCombat();
	
	std::vector<std::vector<std::string>> GetCurrentRoomConnectionsNames();

	void PlayerCheckStats();

	/*
	PlayerInput
	*/
	void ShowInventory();

	void GiveChestOptions();

	void GivePickUpItemsOptions();

	void GiveDoorChoiceOptions();

	////////////////////////////////
	bool myRunGame;

	unsigned int myTurnCount;

	Player myPlayer;
	RoomController myRoomController;

	unsigned int myCurrentRoomIndex;
};

