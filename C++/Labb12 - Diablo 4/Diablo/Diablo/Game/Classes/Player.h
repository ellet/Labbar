#pragma once
#include "Creature.h"
#include "Player\Inventory.h"
#include "Player\SpellBook.h"

class Player
{
public:
	Player();
	~Player();

	Creature & GetCreatureInPlayer();

	void RecalculateInventoryStats();

	void AddItemToInventory(const Item* aItem);

	void GetEquipedPrintableFromInventory(std::vector<std::string> & aStringVectorToAddTo);

	void GetSpellsPrintableFromSpellBook(std::vector<std::string> & aStringVectorToAddTo);

	void PrintPlayerInventory(std::vector<std::string> &  aStringVectorToAddTo) const;

	const Item & GetRefrenceItemFromInventory(const size_t aItemIndex) const;

	void DropItemInInventory(const size_t aItemIndex, const Item* & aItem);

	void GetItemInInventoryInformation(const size_t aItemIndex, std::string & aStringToBuild) const;

	void EquipItemInInventory(const size_t aItemIndex);

	void UnequipItemInInventory(const enumEquipTypes aItemType);

	bool CheckIfItemInInventoryEquipConflict(const size_t aItemIndex);

	void GetCompareString(const size_t aItemIndex, std::string & aStringToBuild);

	const size_t GetInventorySize() const;

	const size_t GetSpellBookSize() const;

	bool IHaveSpellsInSpellBook();
	
	bool IHaveItemsInInventory();

	void ActivateBuff(const size_t aSpellIndex);

private:
	float myPickUpItemStaminaCost;

	SpellBook mySpellBook;
	Creature myCharacter;
	Inventory myInventory;
};

