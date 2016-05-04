#include "stdafx.h"
#include "Door.h"
#include "../../HelpFunctions/HelpFunctions.h"

Door::Door(unsigned int aDoorIndex, unsigned int aFirstRoomIndex, unsigned int aSecondRoomIndex, NameAndDescription aName)
{
	myDoorIndex = aDoorIndex;

	myRoomConnections.push_back(aFirstRoomIndex);
	myRoomConnections.push_back(aSecondRoomIndex);

	myDoorName = aName;
}


Door::~Door()
{
}

const unsigned int Door::GetDoorIndex() const
{
	return myDoorIndex;
}

unsigned int Door::GetOtherRoom(const unsigned int aRoomIndex) const
{
	if (myRoomConnections[0] == aRoomIndex)
	{
		return myRoomConnections[1];
	}
	else
	{
		return myRoomConnections[0];
	}
}

const std::vector<unsigned int>& Door::AccessRoomConnections() const
{
	return myRoomConnections;
}

const std::string & Door::GetDoorName() const
{
	return myDoorName.name;
}