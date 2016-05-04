#include "stdafx.h"
#include "Room.h"
#include "../../HelpFunctions/HelpFunctions.h"

Room::Room()
{
	myName.name = "default name";
	myName.description = "default description";

	myIHaveBeenVisited = false;
	Creature tempCreature = Creature();
	
	tempCreature.SetHealth(25.f);

	StatsManager tempStats;

	tempStats.SetStat(3, enumStatTypes::eStrength);
	tempStats.SetStat(4, enumStatTypes::eIntelligens);
	tempStats.SetStat(4, enumStatTypes::eAgility);
	tempStats.SetStat(2, enumStatTypes::eKondition);

	tempCreature.SetAllStats(tempStats);
	myCreatures.push_back(tempCreature);
}


Room::~Room()
{
}

void Room::InitializeRoom(const NameAndDescription & aName, unsigned int aIndex)
{
	myName = aName;
	myRoomIndex = aIndex;
	myName.description = myName.description + " " + l1functions::ConvertNumberToString(static_cast<int>(myRoomIndex));
}

const std::string & Room::GetRoomName() const
{
	return myName.name;
}

const std::string & Room::GetRoomDescription() const
{
	return myName.description;
}

void Room::AddADoor(const unsigned int aDoorIndex)
{
	myDoors.push_back(aDoorIndex);
}

unsigned int Room::GetRoomIndex() const
{
	return myRoomIndex;
}

unsigned int Room::GetADoorIndex(unsigned int aDoorIndexLocation) const
{
	return myDoors[aDoorIndexLocation];
}

const std::vector<unsigned int> & Room::GetAllDoors() const
{
	return myDoors;
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