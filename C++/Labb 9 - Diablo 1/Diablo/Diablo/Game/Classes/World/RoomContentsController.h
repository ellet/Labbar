#pragma once
#include "../Player/Item.h"
#include <vector>
#include "../NameHolder.h"

class RoomContentsController
{
public:
	RoomContentsController();
	~RoomContentsController();

	Item GetNewItem();

	Buff GetNewTempBuff();

	NameAndDescription GetDoorName();

	NameAndDescription GetARoomName();

private:
	void CreateAllItems();
	
	void CreateAllBuffs();

	void CreateAllTempBuffs();

	void AddDoorNames();
	void AddRoomNames();

	std::vector<Item> myItemTemplates;

	std::vector<Buff> myTempBuffTemplats;

	NameHolder myHolderOfNewDoorNames;
	NameHolder myHolderOfNewRoomsNames;
};