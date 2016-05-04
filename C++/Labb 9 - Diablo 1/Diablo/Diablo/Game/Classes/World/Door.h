#pragma once
#include <vector>
#include "../../Structs/name_and_description.h"
class Door
{
public:
	Door(unsigned int aDoorIndex, unsigned int aFirstRoomIndex, unsigned int aSecondRoomIndex, NameAndDescription aName);
	~Door();

	const unsigned int GetDoorIndex() const;

	unsigned int GetOtherRoom(const unsigned int aRoomIndex) const;

	const std::vector<unsigned int> & AccessRoomConnections() const;

	const std::string & GetDoorName() const;

private:
	unsigned int myDoorIndex;

	NameAndDescription myDoorName;
	std::vector<unsigned int> myRoomConnections;
};

