#include "stdafx.h"
#include "Player.h"
#include "../HelpFunctions/HelpFunctions.h"

Player::Player()
{
	RecalculateInventoryStats();

	

	myCharacter.SetHealth(75.f);

	myCharacter.SetLifeSteal(true);

	StatsManager tempStats;

	tempStats.SetStat(15, enumStatTypes::eStrength);
	tempStats.SetStat(15, enumStatTypes::eIntelligens);
	tempStats.SetStat(15, enumStatTypes::eAgility);
	tempStats.SetStat(15, enumStatTypes::eKondition);
	
	myCharacter.SetAllStats(tempStats);
	myCharacter.SetItemCount(0);

	DamagePower tempDamage = DamagePower(enumAttackTypes::eMagicAttack);

	myCharacter.AddAttack(tempDamage);
}

Player::~Player()
{
}

Creature & Player::GetCreatureInPlayer()
{
	return myCharacter;
}

void Player::RecalculateInventoryStats()
{
	myInventory.RecalculateInventoryStats();
	myCharacter.SendMainBuffsToStatsManager(myInventory.GetInventoryStats());
}

void Player::AddItemToInventory(const Item* aItem)
{
	if (aItem->myItemType < enumEquipTypes::eNonEquip)
	{
		myInventory.SetItemLimit(myCharacter.GetCreatureCarryLimit());
		myCharacter.PayForAction();

		myInventory.AddItem(aItem);
		RecalculateInventoryStats();
	}
	else if (aItem->myItemType == enumEquipTypes::eScroll)
	{
		mySpellBook.AddSpell(aItem);
	}
	else
	{
		l1functions::console::PrintErrorToConsole("Trying too add invalid item type to inventory");
	}
}

void Player::GetEquipedPrintableFromInventory(std::vector<std::string> & aStringVectorToAddTo)
{
	myInventory.EquipedItemsPrintable(aStringVectorToAddTo);
}

void Player::GetSpellsPrintableFromSpellBook(std::vector<std::string>& aStringVectorToAddTo)
{
	mySpellBook.GetSpellsPrintable(aStringVectorToAddTo);
}

void Player::PrintPlayerInventory(std::vector<std::string> &  aStringVectorToAddTo) const
{
	myInventory.PrintInventory(aStringVectorToAddTo);
}

//const Item & Player::GetRefrenceItemFromInventory(const size_t aItemIndex) const
//{
//	return myInventory.GetItemRefrence(aItemIndex);
//}

void Player::DropItemInInventory(const size_t aItemIndex, const Item* & aItem)
{
	myInventory.DropItem(aItemIndex, aItem);
	RecalculateInventoryStats();
}

void Player::GetItemInInventoryInformation(const size_t aItemIndex, std::string & aStringToBuild) const
{
	myInventory.GetItemPrintable(aItemIndex, aStringToBuild);
}

void Player::EquipItemInInventory(const size_t aItemIndex)
{
	myInventory.EquipItem(aItemIndex);
	RecalculateInventoryStats();
}

void Player::UnequipItemInInventory(const enumEquipTypes aItemType)
{
	myInventory.UnequipItem(aItemType);
}

bool Player::CheckIfItemInInventoryEquipConflict(const size_t aItemIndex)
{
	return myInventory.CheckIfItemSlotEquiped(aItemIndex);
}

void Player::GetCompareString(const size_t aItemIndex, std::string & aStringToBuild)
{
	myInventory.GetComparePrintable(aItemIndex, aStringToBuild);
}

const size_t Player::GetInventorySize() const
{
	return myInventory.GetInventorySize();
}

const size_t Player::GetSpellBookSize() const
{
	return mySpellBook.GetSpellBookSize();
}

bool Player::IHaveSpellsInSpellBook()
{
	return mySpellBook.IHaveSpells();
}

bool Player::IHaveItemsInInventory()
{
	return myInventory.IHaveItems();
}

void Player::ActivateBuff(const size_t aSpellIndex)
{
	myCharacter.AddTempBuff(mySpellBook.ActivateSpell(aSpellIndex)->itemBuff);
}