#include "stdafx.h"
#include "Player.h"


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

void Player::AddItemToInventory(const Item & aItem)
{
	myInventory.SetItemLimit(myCharacter.GetCreatureCarryLimit());
	myCharacter.PayForAction();

	myInventory.AddItem(aItem);
	RecalculateInventoryStats();
}

void Player::PrintPlayerInventory() const
{
	myInventory.PrintInventory();
}
                                                                                       