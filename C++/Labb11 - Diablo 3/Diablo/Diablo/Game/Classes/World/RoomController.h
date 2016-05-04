#pragma once
#include <vector>
#include "Room.h"
#include "Door.h"
#include "../NameHolder.h"
#include "Factories\RoomFactory.h"

class RoomController
{
public:
	RoomController();
	~RoomController();

	void CreateRooms();

	unsigned int GetRoomCount();
	unsigned int GetDoorCount();

	Room& AccessRoom(size_t aRoomIndex);
	Door& AccessDoor(size_t aDoorIndex);

	Room* ChangeRoom(const size_t aRoomIndex, const size_t aDoorInRoomIndex);

	void MakeVectorOfDoorNamesInRoom(std::vector<std::string>& aDoorNameVector, Room & aRoom);

	void MakeVectorOfItemNamesInRoom(std::vector<std::string> & aItemNameVector, const size_t aRoomIndex);

	void OnRoomEnterTrigger(Room* aRoom);

	RoomFactory & AccessRoomFactory();

private:

	void CreateAllDoors();

	void CreateRandomDoorRoomConnection(const size_t aDoorIndex);

	Room & RoomController::CreateRoom(const NameAndDescription & aRoomName, const unsigned int aRoomIndex);

	Door & CreateDoor(Room & aRoomIndex, Room & aSecondRoomIndex, const size_t aDoorIndex);

	void DestroyAllRooms();
	void DestroyAllDoors();

	RoomFactory myContentMaker;

	std::vector<Room> myRooms;
	std::vector<Door> myDoors;
};