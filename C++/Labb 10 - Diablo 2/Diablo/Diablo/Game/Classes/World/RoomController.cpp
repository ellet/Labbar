#include "stdafx.h"
#include "RoomController.h"
#include "../../HelpFunctions/HelpFunctions.h"
#include "../../Structs/name_and_description.h"


const size_t RoomAmountToCreate = 25;
const size_t ExtraDoorsToCreate = 5;

RoomController::RoomController()
{
}


RoomController::~RoomController()
{
}

/*
ROOMS
*/

void RoomController::CreateRooms()
{
	DestroyAllDoors();

	myRooms.resize(RoomAmountToCreate);

	for (unsigned int iRoom = 0; iRoom < RoomAmountToCreate; ++iRoom)
	{
		CreateRoom(myContentMaker.GetARoomName(), iRoom);
	}

	CreateAllDoors();
}




Room & RoomController::AccessRoom(size_t aRoomIndex)
{
	return myRooms[aRoomIndex];
}


Room & RoomController::CreateRoom(const NameAndDescription & aRoomName, const unsigned int aRoomIndex)
{
	Room tmpRoom;
	tmpRoom.InitializeRoom(aRoomName, aRoomIndex);

	myRooms[aRoomIndex] = tmpRoom;
	return AccessRoom(tmpRoom.GetRoomIndex());
}



void RoomController::OnRoomEnterTrigger(Room* aRoom)
{
	if ((*aRoom).CheckIfVisited() == false)
	{
		(*aRoom).VisitRoom();
		myContentMaker.RoomSetup(aRoom);
	}
}
RoomFactory & RoomController::AccessRoomFactory()
{
	return myContentMaker;
}
/*

Both Rooms And Doors

*/




void RoomController::CreateAllDoors()
{
	myDoors.resize(RoomAmountToCreate + ExtraDoorsToCreate -1 + 50);

	for (size_t iRoom = 0; iRoom < static_cast<size_t>(myRooms.size()-1); ++iRoom)
	{
		CreateDoor(AccessRoom(iRoom) , AccessRoom(iRoom + 1), iRoom);
	}

	for (size_t iRoom = myRooms.size() - 1; iRoom < (myRooms.size() - 1) + ExtraDoorsToCreate; ++iRoom)
	{
		CreateRandomDoorRoomConnection(iRoom);
	}
}

void RoomController::CreateRandomDoorRoomConnection(const size_t aDoorIndex)
{
	unsigned int aFirstRoom = l1functions::math::GetRandomNumberSigned(static_cast<unsigned int>(myRooms.size()));

	unsigned int aSecondRoom; 
	do
	{
		aSecondRoom = l1functions::math::GetRandomNumberSigned(static_cast<unsigned int>(myRooms.size()));
	} while (aFirstRoom == aSecondRoom);

	CreateDoor(myRooms[aFirstRoom], myRooms[aSecondRoom], aDoorIndex);
}



/*
DOORS

*/



Door & RoomController::CreateDoor(Room & aFirstRoom, Room & aSecondRoom, const size_t aDoorIndex)
{
	Door tmpDoor;
	tmpDoor.SetupDoor(aDoorIndex, &aFirstRoom, &aSecondRoom, myContentMaker.GetDoorName());
	myDoors[aDoorIndex] = tmpDoor;

	aFirstRoom.AddADoor(myDoors[aDoorIndex]);
	aSecondRoom.AddADoor(myDoors[aDoorIndex]);

	
	return AccessDoor(tmpDoor.GetDoorIndex());
}

Door & RoomController::AccessDoor(size_t aDoorIndex)
{
	return myDoors[aDoorIndex];
}

Room* RoomController::ChangeRoom(const size_t aRoomIndex, const size_t aDoorIndex)
{
	Room* tempRoomIndexHolder = AccessDoor(aDoorIndex).GetOtherRoom(aRoomIndex);
	OnRoomEnterTrigger(tempRoomIndexHolder);

	return tempRoomIndexHolder;
}

void RoomController::MakeVectorOfDoorNamesInRoom(std::vector<std::string>& aDoorNameVector, Room & aRoom)
{
	const std::vector<Door*> & DoorIndexes = aRoom.GetAllDoors();

	for (unsigned int iDoor = 0; iDoor < DoorIndexes.size(); ++iDoor)
	{
		std::string tempString = (*DoorIndexes[iDoor]).GetDoorName();

		const Room & OtherRoomToCheck = (*(*DoorIndexes[iDoor]).GetOtherRoom(aRoom.GetRoomIndex()));

		if (OtherRoomToCheck.CheckIfVisited() == true)
		{
			tempString += " <Visited>";
		}

		aDoorNameVector.push_back(tempString);
	}
}

void RoomController::MakeVectorOfItemNamesInRoom(std::vector<std::string>& aItemNameVector, const size_t aRoomIndex)
{
	const std::vector<Item>Items = AccessRoom(aRoomIndex).GetRoomItems();

	for (unsigned int iItem = 0; iItem < Items.size(); ++iItem)
	{
		aItemNameVector.push_back(Items[iItem].itemNameAndDescription.name);
	}
}

//////////////////////
unsigned int RoomController::GetRoomCount()
{
	return static_cast<unsigned int>(myRooms.size());
}

unsigned int RoomController::GetDoorCount()
{
	return static_cast<unsigned int>(myDoors.size());
}


void RoomController::DestroyAllRooms()
{
	if (myDoors.size() > 0)
	{
		DestroyAllDoors();
	}

	myRooms.clear();
}

void RoomController::DestroyAllDoors()
{
	if (myRooms.size() > 0)
	{
		DestroyAllDoors();
	}

	myDoors.clear();
}
