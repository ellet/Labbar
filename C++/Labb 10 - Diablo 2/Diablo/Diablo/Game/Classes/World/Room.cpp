#include "stdafx.h"
#include "Room.h"
#include "../../HelpFunctions/HelpFunctions.h"
#include "Door.h"

Room::Room()
{
	myName.name = "default name";
	myName.description = "default description";

	myIHaveBeenVisited = false;
}


Room::~Room()
{
}

void Room::InitializeRoom(const NameAndDescription & aName, unsigned int aIndex)
{
	myName = aName;
	//myName.name += " " + l1functions::ConvertNumberToString(static_cast<int>(myRoomIndex));
	myRoomIndex = aIndex;
}

const std::string & Room::GetRoomName() const
{
	return myName.name;
}

const std::string & Room::GetRoomDescription() const
{
	return myName.description;
}

void Room::AddADoor(Door & aDoor)
{
	myDoors.push_back(&aDoor);
}

unsigned int Room::GetRoomIndex() const
{
	return myRoomIndex;
}

size_t Room::GetADoorIndex(const size_t aDoorIndexLocation) const
{
	return (*myDoors[aDoorIndexLocation]).GetDoorIndex();
}

const std::vector<Door*> & Room::GetAllDoors() const
{
	return myDoors;
}

void Room::AddCreatureToRoom(const Creature & aCreature)
{
	myCreatures.push_back(aCreature);
}

Creature & Room::GetCreatureInRoom()
{
	return myCreatures[0];
}

bool Room::IHaveItems() const
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

Chest & Room::GetChestInRoom()
{
	return myChests[0];
}


std::vector<Item>& Room::GetRoomItems()
{
	return myItems;
}

void Room::AddItem(const Item & aItemToAddToRoom)
{
	myItems.push_back(aItemToAddToRoom);
}

void Room::AddChestToRoom(const Chest & aChestToAddToRoom)
{
	myChests.push_back(aChestToAddToRoom);
}

bool Room::IHaveChests()
{
	if (myChests.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Room::IHaveCreatures()
{
	if (myCreatures.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Room::IHaveBuffs() const
{
	if (myBuffs.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Room::RemoveAllCreatures()
{
	myCreatures.clear();
}

bool Room::CheckIfVisited() const
{
	return myIHaveBeenVisited;
}

void Room::VisitRoom()
{
	myIHaveBeenVisited = true;
}

Item Room::ItemPickedUp(unsigned int aItemIndex)
{
	const Item ItemHolder = myItems[aItemIndex];
	myItems.erase(myItems.begin() + aItemIndex);

	return ItemHolder;
}

Buff Room::BuffPickedUp()
{
	const Buff BuffHolder = myBuffs[0];
	myBuffs.erase(myBuffs.begin());

	return BuffHolder;
}

void Room::AddBuffToRoom(const Buff & aBuff)
{
	myBuffs.push_back(aBuff);
}