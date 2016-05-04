#pragma once
#include <string>
#include "Stats\VitalStat.h"
#include "../Structs/name_and_description.h"
#include "DamagePower.h"
#include "Stats\StatsManager.h"
#include "Stats\VitalsManager.h"
#include "DamageManager.h"

class Creature
{
public:
	Creature();
	~Creature();

	void AddAttack(DamagePower & aNewAttackToAdd);

	void SetAllStats(const StatsManager & aNewStatsManager);

	void AddTempBuff(const Buff & aBuff);

	void SetName(NameAndDescription aNameAndDescription);

	const std::string& Creature::GetName() const;

	const float DealDamage(const unsigned int AttackToDo);

	float TakeDamage(const float aDamageAmount);

	unsigned int GetCreatureCarryLimit();

	float GetCreatureHitPoints() const;

	float GetHealthPercentage() const;

	void SetStamina(const float aNewStaminaValue);

	void SetHealth(const float aNewHealthValue);
	
	bool GetHasEnergy() const;

	bool GetIsAlive(const bool aPrintIfDied = true) const;

	const unsigned int GetStatValue(const enumStatTypes aStatToCheck) const;

	void PayForAction(const float aActionCost = 1.f);

	void PrintHealth() const;

	void SendMainBuffsToStatsManager(const std::vector<Buff> & aVectorOfBuffs );

	void PrintCreatureStats() const;

	void PrintCreatureVitals() const;

	void SetItemCount(unsigned int aItemCount);

	unsigned int GetItemCount();

	unsigned int GetBuffCount();

	void RoundCheckTrigger(const unsigned int aTurnCount);

	void ConstructVectorOfNamesOfAttack(std::vector<std::string> & aVectorOfStringsToBuild);

	void DoLifeSteal(const float aLifeStealAmount);

	void SetLifeSteal(const bool aIHaveLifeSteal);

private:
	bool myIHaveLifeSteal;
	void GetPrintOfCreatureDamageRange(const unsigned int aAttackToCheck, std::string & aStringtoAddTo) const;
	unsigned int myItemCount;
	unsigned int myBuffCount;

	void RecalculateStatBasedActions();
	void RecalculateAllVitals();
	void RecalculateAllDamage();

	NameAndDescription myNameAndDescription;
	
	DamageManager myDamageManager;
	VitalsManager myVitals;
	StatsManager myStatsManager;
	std::vector<DamagePower> myAttacks;
};