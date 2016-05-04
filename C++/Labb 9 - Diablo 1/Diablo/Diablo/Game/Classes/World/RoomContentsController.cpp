#include "stdafx.h"
#include "RoomContentsController.h"


RoomContentsController::RoomContentsController()
{
	CreateAllItems();
	CreateAllBuffs();

	AddDoorNames();
	AddRoomNames();
}


RoomContentsController::~RoomContentsController()
{
}

Item RoomContentsController::GetNewItem()
{
	return myItemTemplates[0];
}

Buff RoomContentsController::GetNewTempBuff()
{
	return myTempBuffTemplats[0];
}

NameAndDescription RoomContentsController::GetDoorName()
{
	return myHolderOfNewDoorNames.GetAName();
}

NameAndDescription RoomContentsController::GetARoomName()
{
	return myHolderOfNewRoomsNames.GetAName();
}

void RoomContentsController::CreateAllItems()
{
	Item tmpItem;

	tmpItem.itemBuff.Initialize(3, enumItemTypes::eStats, 0, enumStatTypes::eIntelligens);
	tmpItem.itemNameAndDescription.name = "Test Item 1";
	tmpItem.itemNameAndDescription.name = "Test Item 1 Description";
	myItemTemplates.push_back(tmpItem);

	tmpItem.itemBuff.Initialize(3, enumItemTypes::eStats, 0, enumStatTypes::eIntelligens);
	tmpItem.itemNameAndDescription.name = "Test Item 2";
	tmpItem.itemNameAndDescription.name = "Test Item 2 Description";
	myItemTemplates.push_back(tmpItem);
}

void RoomContentsController::CreateAllBuffs()
{
	CreateAllTempBuffs();
}

void RoomContentsController::CreateAllTempBuffs()
{
	Buff tempBuff;

	tempBuff.Initialize(3, enumItemTypes::eStats, 3, enumStatTypes::eIntelligens);
	myTempBuffTemplats.push_back(tempBuff);
}


void RoomContentsController::AddDoorNames()
{
	std::vector<NameAndDescription> doorNames;
	NameAndDescription temp;
	temp.name = "pink";
	temp.description = "the door is pink";
	doorNames.push_back(temp);

	temp.name = "black";
	temp.description = "the door is black";
	doorNames.push_back(temp);

	temp.name = "blue";
	temp.description = "the door is blue";
	doorNames.push_back(temp);

	temp.name = "purple";
	temp.description = "the door is purple";
	doorNames.push_back(temp);

	temp.name = "yellow";
	temp.description = "the door is yellow";
	doorNames.push_back(temp);

	temp.name = "brown";
	temp.description = "the door is yellow";
	doorNames.push_back(temp);

	temp.name = "teal";
	temp.description = "the door is teal";
	doorNames.push_back(temp);

	temp.name = "white";
	temp.description = "the door is white";
	doorNames.push_back(temp);

	temp.name = "sandy";
	temp.description = "the door is sandy";
	doorNames.push_back(temp);



	myHolderOfNewDoorNames.AddNamesToHold(doorNames);
}

void RoomContentsController::AddRoomNames()
{
	std::vector<NameAndDescription> roomNames;

	NameAndDescription temp;
	temp.name = "happy place";
	temp.description = "the place is very happy";
	roomNames.push_back(temp);

	temp.name = "Qwerty place";
	temp.description = "the place is very qwerty";
	roomNames.push_back(temp);

	temp.name = "kamel place";
	temp.description = "the place is very kamely";
	roomNames.push_back(temp);

	temp.name = "snarky place";
	temp.description = "the place is very snarky";
	roomNames.push_back(temp);

	temp.name = "left place";
	temp.description = "the place is very left";
	roomNames.push_back(temp);



	myHolderOfNewRoomsNames.AddNamesToHold(roomNames);
}