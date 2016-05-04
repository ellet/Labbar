#pragma once
#include <vector>
#include "../../Structs/name_and_description.h"
class Room;
class Door
{
public:
	Door();
	~Door();

	void SetupDoor(size_t aDoorIndex, Room* aFirstRoomIndex, Room* aSecondRoomIndex, NameAndDescription aName);

	const size_t GetDoorIndex() const;

	Room* GetOtherRoom(const size_t aRoomIndex) const;

	const std::vector<Room*> & AccessRoomConnections() const;

	const std::string & GetDoorName() const;

private:
	size_t myDoorIndex;

	NameAndDescription myDoorName;
	std::vector<Room*> myRoomConnections;
};

