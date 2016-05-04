#pragma once
#include <string>
#include <vector>
#include "../../Structs/name_and_description.h"
#include "../Creature.h"
#include "../Player/Item.h"
#include "../Chest.h"

class Door;
class Room
{
public:
	Room();
	~Room();

	void InitializeRoom(const NameAndDescription & aName, unsigned int aIndex);

	const std::string& GetRoomName() const;

	const std::string& GetRoomDescription() const;

	void AddADoor(Door &aDoorIndex);

	unsigned int GetRoomIndex() const;

	size_t GetADoorIndex(const size_t) const;

	const std::vector<Door*>& GetAllDoors() const;

	void AddCreatureToRoom(const Creature & aCreature);

	Creature & GetCreatureInRoom();

	bool IHaveItems() const;

	Chest & GetChestInRoom();

	std::vector<const Item*> & GetRoomItems();

	void AddItem(const Item* aItemToAddToRoom);

	void AddChestToRoom(const Chest & aChestToAddToRoom);

	bool IHaveChests();

	bool IHaveCreatures();

	bool IHaveBuffs() const;

	void RemoveAllCreatures();

	bool CheckIfVisited() const;

	void VisitRoom();

	const Item* ItemPickedUp(unsigned int aItemIndex);

	Buff BuffPickedUp();

	void AddBuffToRoom(const Buff & aBuff);

private:
	unsigned int myRoomIndex;
	NameAndDescription myName;
	
	bool myIHaveBeenVisited;

	std::vector<Buff> myBuffs;
	std::vector<Creature> myCreatures;
	std::vector<const Item*> myItems;
	std::vector<Chest> myChests;
	std::vector<Door*> myDoors;
};