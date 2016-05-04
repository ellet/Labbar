#include "stdafx.h"
#include "RoomFactory.h"
#include "../../../HelpFunctions/HelpFunctions.h"

RoomFactory::RoomFactory()
{
	AddDoorNames();
	AddRoomNames();
}


RoomFactory::~RoomFactory()
{
}

void RoomFactory::RoomSetup(Room* aRoom)
{

	(*aRoom).AddCreatureToRoom(myEnemyFactory.GetNewCreature());

	if (l1functions::math::RandomChanceHappend(25))
	{
		const unsigned int aItemCount = l1functions::math::GetRandomNumberSigned(2, 1);

		AddItemsToRoom(aItemCount, aRoom);
	}

	if (l1functions::math::RandomChanceHappend(45))
	{
		const unsigned int aBuffCount = l1functions::math::GetRandomNumberSigned(2, 1);

		AddBuffsToRoom(aBuffCount, aRoom);
	}

	if (l1functions::math::RandomChanceHappend(25))
	{
		const unsigned int aChestCount = 1;//l1functions::math::GetRandomNumberSigned(2, 1);

		AddChestsToRoom(aChestCount, aRoom);
	}
}

void RoomFactory::AddItemsToRoom(const unsigned int aItemAmount, Room* aRoom)
{
	for (unsigned int iItem = 0; iItem < aItemAmount; ++iItem)
	{
		(*aRoom).AddItem((*myItemFactory.GetNewItem()));
	}
}

void RoomFactory::AddBuffsToRoom(const unsigned int aBuffAmount, Room* aRoom)
{
	for (unsigned int iBuff = 0; iBuff < aBuffAmount; ++iBuff)
	{
		(*aRoom).AddBuffToRoom((*myItemFactory.GetNewBuff()));
	}
}

void RoomFactory::AddChestsToRoom(const unsigned int aChestAmount, Room* aRoom)
{
	for (unsigned int iBuff = 0; iBuff < aChestAmount; ++iBuff)
	{
		Chest tempChest;

		tempChest.AddItem((*myItemFactory.GetNewItem()));
		tempChest.AddItem((*myItemFactory.GetNewItem()));
		tempChest.AddItem((*myItemFactory.GetNewItem()));

		(*aRoom).AddChestToRoom(tempChest);
	}
}




NameAndDescription RoomFactory::GetDoorName()
{
	return myHolderOfNewDoorNames.GetAName();
}

NameAndDescription RoomFactory::GetARoomName()
{
	return myHolderOfNewRoomsNames.GetAName();
}





void RoomFactory::AddDoorNames()
{
	std::vector<NameAndDescription> doorNames;
	NameAndDescription temp;
	temp.name = "pink";
	temp.description = "the door is pink";
	doorNames.push_back(temp);

	temp.name = "black";
	temp.description = "the door is black";
	doorNames.push_back(temp);

	temp.name = "blue";
	temp.description = "the door is blue";
	doorNames.push_back(temp);

	temp.name = "purple";
	temp.description = "the door is purple";
	doorNames.push_back(temp);

	temp.name = "yellow";
	temp.description = "the door is yellow";
	doorNames.push_back(temp);

	temp.name = "brown";
	temp.description = "the door is yellow";
	doorNames.push_back(temp);

	temp.name = "teal";
	temp.description = "the door is teal";
	doorNames.push_back(temp);

	temp.name = "white";
	temp.description = "the door is white";
	doorNames.push_back(temp);

	temp.name = "sandy";
	temp.description = "the door is sandy";
	doorNames.push_back(temp);



	myHolderOfNewDoorNames.AddNamesToHold(doorNames);
}

void RoomFactory::AddRoomNames()
{
	std::vector<NameAndDescription> roomNames;

	NameAndDescription temp;
	temp.name = "happy place";
	temp.description = "the place is very happy";
	roomNames.push_back(temp);

	temp.name = "Qwerty place";
	temp.description = "the place is very qwerty";
	roomNames.push_back(temp);

	temp.name = "kamel place";
	temp.description = "the place is very kamely";
	roomNames.push_back(temp);

	temp.name = "snarky place";
	temp.description = "the place is very snarky";
	roomNames.push_back(temp);

	temp.name = "left place";
	temp.description = "the place is very left";
	roomNames.push_back(temp);



	myHolderOfNewRoomsNames.AddNamesToHold(roomNames);
}