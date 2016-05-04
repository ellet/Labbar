#include "stdafx.h"
#include "RoomController.h"
#include "../../HelpFunctions/HelpFunctions.h"
#include "../../Structs/name_and_description.h"

RoomController::RoomController()
{
}


RoomController::~RoomController()
{
}

/*
ROOMS
*/

void RoomController::CreateRooms(const unsigned int aNumberOfRoomsToCreate)
{
	DestroyAllDoors();

	for (unsigned int iRoom = 0; iRoom < aNumberOfRoomsToCreate; ++iRoom)
	{
		CreateRoom(myContentMaker.GetARoomName(), iRoom);
	}

	CreateAllDoors(2);
}

void RoomController::AddItemsToRoom(const unsigned int aItemAmount, const unsigned int aRoomIndex)
{
	Room &roomToAddItemTo = AccessRoom(aRoomIndex);
	
	for (unsigned int iItem = 0; iItem < aItemAmount; ++iItem)
	{
		roomToAddItemTo.AddItem(myContentMaker.GetNewItem());
	}
}

void RoomController::AddBuffsToRoom(const unsigned int aBuffAmount, const unsigned int aRoomIndex)
{
	Room &roomToAddBuffTo = AccessRoom(aRoomIndex);

	for (unsigned int iBuff= 0; iBuff < aBuffAmount; ++iBuff)
	{
		roomToAddBuffTo.AddBuffToRoom(myContentMaker.GetNewTempBuff());
	}
}

void RoomController::AddChestsToRoom(const unsigned int aChestAmount, const unsigned int aRoomIndex)
{
	Room &roomToAddChestTo = AccessRoom(aRoomIndex);

	for (unsigned int iBuff = 0; iBuff < aChestAmount; ++iBuff)
	{
		Chest tempChest;

		tempChest.AddItem(myContentMaker.GetNewItem());
		tempChest.AddItem(myContentMaker.GetNewItem());
		tempChest.AddItem(myContentMaker.GetNewItem());

		roomToAddChestTo.AddChestToRoom(tempChest);
	}
}


Room & RoomController::AccessRoom(unsigned int aRoomIndex)
{
	return myRooms[aRoomIndex];
}


Room & RoomController::CreateRoom(const NameAndDescription & aRoomName, const unsigned int aRoomIndex)
{
	Room tmpRoom;
	tmpRoom.InitializeRoom(aRoomName, aRoomIndex);

	myRooms.push_back(tmpRoom);
	return AccessRoom(tmpRoom.GetRoomIndex());
}

void RoomController::RoomSetup(const unsigned int aRoomIndex)
{
	if (l1functions::math::RandomChanceHappend(25))
	{
		const unsigned int aItemCount = l1functions::math::GetRandomNumberSigned(2, 1);

		AddItemsToRoom(aItemCount, aRoomIndex);
	}

	if (l1functions::math::RandomChanceHappend(45))
	{
		const unsigned int aBuffCount = l1functions::math::GetRandomNumberSigned(2, 1);

		AddBuffsToRoom(aBuffCount, aRoomIndex);
	}

	if (l1functions::math::RandomChanceHappend(25))
	{
		const unsigned int aChestCount = 1;//l1functions::math::GetRandomNumberSigned(2, 1);

		AddChestsToRoom(aChestCount, aRoomIndex);
	}
}

void RoomController::OnRoomEnterTrigger(const unsigned aRoomIndex)
{
	Room &roomToTrigger = AccessRoom(aRoomIndex);

	if (roomToTrigger.CheckIfVisited() == false)
	{
		roomToTrigger.VisitRoom();
		RoomSetup(aRoomIndex);
	}
}
/*

Both Rooms And Doors

*/




void RoomController::CreateAllDoors(const unsigned int aExtraDoorsToCreate)
{
	for (unsigned int iRoom = 0; iRoom < myRooms.size()-1; ++iRoom)
	{
		CreateDoor(AccessRoom(iRoom).GetRoomIndex(), AccessRoom(iRoom + 1).GetRoomIndex());		
	}

	for (unsigned int iRoom = 0; iRoom < aExtraDoorsToCreate; ++iRoom)
	{
		CreateRandomDoorRoomConnection();
	}
}

void RoomController::CreateRandomDoorRoomConnection()
{
	unsigned int aFirstRoom = l1functions::math::GetRandomNumberSigned(static_cast<unsigned int>(myRooms.size()));

	unsigned int aSecondRoom; 
	do
	{
		aSecondRoom = l1functions::math::GetRandomNumberSigned(static_cast<unsigned int>(myRooms.size()));
	} while (aFirstRoom == aSecondRoom);

	CreateDoor(aFirstRoom, aSecondRoom);
}



/*
DOORS

*/



Door & RoomController::CreateDoor(unsigned int aFirstRoomIndex, unsigned int aSecondRoomIndex)
{
	Door tmpDoor(static_cast<unsigned int>(myDoors.size()), aFirstRoomIndex, aSecondRoomIndex, myContentMaker.GetDoorName());
	
	AccessRoom(aFirstRoomIndex).AddADoor(tmpDoor.GetDoorIndex());
	AccessRoom(aSecondRoomIndex).AddADoor(tmpDoor.GetDoorIndex());

	myDoors.push_back(tmpDoor);
	return AccessDoor(tmpDoor.GetDoorIndex());
}

Door & RoomController::AccessDoor(unsigned int aDoorIndex)
{
	return myDoors[aDoorIndex];
}

unsigned int RoomController::ChangeRoom(const unsigned int aRoomIndex, const int aDoorIndex)
{
	unsigned int tempRoomIndexHolder = AccessDoor(aDoorIndex).GetOtherRoom(aRoomIndex);
	OnRoomEnterTrigger(tempRoomIndexHolder);

	return tempRoomIndexHolder;
}

void RoomController::MakeVectorOfDoorNamesInRoom(std::vector<std::string>& aDoorNameVector, const unsigned int aRoomIndex)
{
	const std::vector<unsigned int>DoorIndexes = AccessRoom(aRoomIndex).GetAllDoors();

	for (unsigned int iDoor = 0; iDoor < DoorIndexes.size(); ++iDoor)
	{
		std::string tempString = AccessDoor(DoorIndexes[iDoor]).GetDoorName();

		if (AccessRoom(AccessDoor(DoorIndexes[iDoor]).GetOtherRoom(aRoomIndex)).CheckIfVisited() == true)
		{
			tempString += " <Visited>";
		}

		aDoorNameVector.push_back(tempString);
	}
}

void RoomController::MakeVectorOfItemNamesInRoom(std::vector<std::string>& aItemNameVector, const unsigned int aRoomIndex)
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
