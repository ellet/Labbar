#include "stdafx.h"
#include "Door.h"
#include "../../HelpFunctions/HelpFunctions.h"
#include "Room.h"

Door::Door()
{
}


Door::~Door()
{
}

void Door::SetupDoor(size_t aDoorIndex, Room * aFirstRoomIndex, Room * aSecondRoomIndex, NameAndDescription aName)
{
	myDoorIndex = aDoorIndex;

	myRoomConnections.push_back(aFirstRoomIndex);
	myRoomConnections.push_back(aSecondRoomIndex);

	myDoorName = aName;
}

const size_t Door::GetDoorIndex() const
{
	return myDoorIndex;
}

Room* Door::GetOtherRoom(const size_t aRoomIndex) const
{
	if ((*myRoomConnections[0]).GetRoomIndex() == aRoomIndex)
	{
		return myRoomConnections[1];
	}
	else
	{
		return myRoomConnections[0];
	}
}

const std::vector<Room*>& Door::AccessRoomConnections() const
{
	return myRoomConnections;
}

const std::string & Door::GetDoorName() const
{
	return myDoorName.name;
}