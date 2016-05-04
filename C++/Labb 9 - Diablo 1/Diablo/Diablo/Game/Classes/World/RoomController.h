#pragma once
#include <vector>
#include "Room.h"
#include "Door.h"
#include "../NameHolder.h"
#include "RoomContentsController.h"

class RoomController
{
public:
	RoomController();
	~RoomController();

	void CreateRooms(const unsigned int aNumberOfRoomsToCreate);

	void AddItemsToRoom(const unsigned int aItemAmount, const unsigned int aRoomIndex);

	void AddBuffsToRoom(const unsigned int aBuffAmount, const unsigned int aRoomIndex);

	void AddChestsToRoom(const unsigned int aChestAmount, const unsigned int aRoomIndex);

	unsigned int GetRoomCount();
	unsigned int GetDoorCount();

	Room& AccessRoom(unsigned int aRoomIndex);
	Door& AccessDoor(unsigned int aDoorIndex);

	unsigned int ChangeRoom(const unsigned int aRoomIndex, const int aDoorInRoomIndex);

	void RoomSetup(const unsigned int aRoomIndex);

	void MakeVectorOfDoorNamesInRoom(std::vector<std::string> & aDoorNameVector, const unsigned int aRoomIndex);

	void MakeVectorOfItemNamesInRoom(std::vector<std::string> & aItemNameVector, const unsigned int aRoomIndex);

	void OnRoomEnterTrigger(const unsigned aRoomIndex);

private:

	void CreateAllDoors(const unsigned int aExtraDoorsToCreate);

	void CreateRandomDoorRoomConnection();

	Room & RoomController::CreateRoom(const NameAndDescription & aRoomName, const unsigned int aRoomIndex);

	Door & CreateDoor(unsigned int aRoomIndex, unsigned int aSecondRoomIndex);

	void DestroyAllRooms();
	void DestroyAllDoors();

	RoomContentsController myContentMaker;

	std::vector<Room> myRooms;
	std::vector<Door> myDoors;
};