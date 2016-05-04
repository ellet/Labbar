#pragma once
#include "Creature.h"
#include "Player\Inventory.h"

class Player
{
public:
	Player();
	~Player();

	Creature & GetCreatureInPlayer();

	void RecalculateInventoryStats();

	void AddItemToInventory(const Item & aItem);

	void PrintPlayerInventory() const;

private:
	float myPickUpItemStaminaCost;

	Creature myCharacter;
	Inventory myInventory;
};

