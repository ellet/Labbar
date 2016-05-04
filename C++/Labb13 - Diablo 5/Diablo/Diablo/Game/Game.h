#pragma once
#include "Classes\Creature.h"
#include "Classes\World\RoomController.h"
#include "Classes\Player.h"
#include "Classes\Menu\MenuOptionsEnum.h"
#include "Classes\Menu\InventoryOptions.h"


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

	void PlayerChangeRoom(const size_t aDoorInRoomIndex);

	void PlayerPickUpItem(const unsigned int aItemToPickUp);

	void BuildInventoryOptionsMenu(std::vector<enumInventoryOptions> & aMenuHolderToBuild);

	void BuildExplorerMenu(std::vector<enumMenuOptions> & aMenuHolderToBuild);

	void TriggerMenuOption(enumMenuOptions);

	void PlayerEnterCombat();
	
	std::vector<std::vector<std::string>> GetCurrentRoomConnectionsNames();

	void PlayerCheckStats();

	/*
	PlayerInput
	*/
	void ShowInventory();

	void ShowSpellBook();

	void GiveActivateSpellOptions();

	void GiveShortCutSpellOptions();

	void GiveDropItemOptions();

	void GiveEquipItemOptions();

	void GiveUnequipItemOptions();

	void GiveItemCheckOptions();

	const size_t ChooseItemInInventory();

	const size_t ChooseSpellInSpellBook();

	void GiveChestOptions();

	void GivePickUpItemsOptions();

	void GiveDoorChoiceOptions();

	////////////////////////////////
	bool myRunGame;

	unsigned int myTurnCount;

	Player myPlayer;
	RoomController myRoomController;

	size_t myCurrentRoomIndex;
};