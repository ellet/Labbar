#pragma once
#include "../../Player/Item.h"
#include <vector>
#include "../../NameHolder.h"
#include "ItemFactory.h"
#include "EnemyFactory.h"
#include "../Room.h"

class RoomFactory
{
public:
	RoomFactory();
	~RoomFactory();

	NameAndDescription GetDoorName();

	NameAndDescription GetARoomName();

	void RoomSetup(Room* aRoom);

	void AddItemsToRoom(const unsigned int aItemAmount, Room* aRoom);

	void AddBuffsToRoom(const unsigned int aBuffAmount, Room* aRoom);

	void AddChestsToRoom(const unsigned int aChestAmount, Room* aRoom);

private:
	void AddDoorNames();
	void AddRoomNames();

	NameHolder myHolderOfNewDoorNames;
	NameHolder myHolderOfNewRoomsNames;

	EnemyFactory myEnemyFactory;
	ItemFactory myItemFactory;
};