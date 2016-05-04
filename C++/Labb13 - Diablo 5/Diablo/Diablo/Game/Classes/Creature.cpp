#include "stdafx.h"
#include "Creature.h"
#include "../HelpFunctions/HelpFunctions.h"
#include "Stats\AttackTypesEnum.h"
#include "Stats\enumVitalTypes.h"

Creature::Creature()
{
	myNameAndDescription.name = "default name";
	myNameAndDescription.description = "default description";
	
	DamagePower tempDamage = DamagePower(enumAttackTypes::eNormalAttack);

	AddAttack(tempDamage);

	RecalculateStatBasedActions();

	myIHaveLifeSteal = false;

	if (l1functions::math::RandomChanceHappend(75, true) == true)
	{
		myItemCount = 1;
	}
	else
	{
		myItemCount = 0;
	}

	if (l1functions::math::RandomChanceHappend(25, true) == true)
	{
		myBuffCount = 1;
	}
	else
	{
		myBuffCount = 0;
	}
}

Creature::~Creature()
{
}

void Creature::AddAttack(DamagePower & aNewAttackToAdd)
{
	myAttacks.push_back(aNewAttackToAdd);
}

void Creature::SetAllStats(const StatsManager & aNewStatsManager)
{
	myStatsManager = aNewStatsManager;
	RecalculateStatBasedActions();
}

void Creature::AddTempBuff(const Buff & aBuff)
{
	myStatsManager.AddTempBuffToStat(aBuff);
	RecalculateStatBasedActions();
}

void Creature::SetName(NameAndDescription aNameAndDescription)
{
	myNameAndDescription = aNameAndDescription;
}

const std::string& Creature::GetName() const
{
	return myNameAndDescription.name;
}

const float Creature::DealDamage(const unsigned int aAttackToDo)
{
	const float DamagetoDeal = myAttacks[aAttackToDo].GetDamageToDeal();
	l1functions::console::PrintToConsole(myNameAndDescription.name, false);
	l1functions::console::PrintToConsole(" deals ", false);
	l1functions::console::PrintNumberToConsole(DamagetoDeal, false);
	l1functions::console::PrintToConsole(" damage.");

	myVitals.ChangeVital(-myAttacks[aAttackToDo].GetStaminaCost(), enumVitalTypes::eStamina);
	return DamagetoDeal;
}

float Creature::TakeDamage(const float aDamageAmount)
{
	const float DamageToTake = aDamageAmount - (myVitals.GetVitalStat(enumVitalTypes::eDefense).GetVitalValue());

	if (DamageToTake > 0)
	{
		l1functions::console::PrintToConsole(myNameAndDescription.name, false);
		l1functions::console::PrintToConsole(" takes ", false);
		l1functions::console::PrintNumberToConsole(DamageToTake, false);
		l1functions::console::PrintToConsole(" damage.");
		myVitals.ChangeVital(-DamageToTake, enumVitalTypes::eHealth);
	}
	else
	{
		l1functions::console::PrintErrorToConsole("Damage recieved is negative");
	}

	return DamageToTake;
}

unsigned int Creature::GetCreatureCarryLimit()
{
	return static_cast<unsigned int>(myVitals.GetVitalValue(enumVitalTypes::eCarryLimit));
}

void Creature::PrintHealth() const
{
	l1functions::console::PrintToConsole(myNameAndDescription.name, false);
	l1functions::console::PrintToConsole(" health is ", false);
	l1functions::console::PrintNumberToConsole(myVitals.GetVitalValue(enumVitalTypes::eHealth), false);
	l1functions::console::PrintToConsole(" hit points.");
}

void Creature::SendMainBuffsToStatsManager(const std::vector<Buff>& aVectorOfBuffs)
{
	myStatsManager.ReceiveMainBuffs(aVectorOfBuffs);
	RecalculateStatBasedActions();
}

void Creature::GetPrintOfCreatureDamageRange(const unsigned int aAttackToCheck, std::string & aStringtoAddTo) const
{
	myAttacks[aAttackToCheck].GetName(aStringtoAddTo);
	aStringtoAddTo += " has a damage range of ";
	myAttacks[aAttackToCheck].GetPrintOfDamageRange(aStringtoAddTo);
}

void Creature::PrintCreatureStats() const
{
	myStatsManager.PrintStats();
}

void Creature::PrintCreatureVitals() const
{
	myVitals.PrintVitals();
}

void Creature::SetItemCount(unsigned int aItemCount)
{
	myItemCount = aItemCount;
}

unsigned int Creature::GetItemCount()
{
	return myItemCount;
}

unsigned int Creature::GetBuffCount()
{
	return myBuffCount;
}

void Creature::RoundCheckTrigger(const unsigned int aTurnCount)
{
	myStatsManager.TimeCheckTrigger(aTurnCount);
}

void Creature::ConstructVectorOfNamesOfAttack(std::vector<std::string>& aVectorOfStringsToBuild)
{
	for (unsigned int iAttack = 0; iAttack < myAttacks.size(); ++iAttack)
	{
		std::string tempString;
		GetPrintOfCreatureDamageRange(iAttack, tempString);
		aVectorOfStringsToBuild.push_back(tempString);
	}
}

void Creature::DoLifeSteal(const float aLifeStealAmount)
{
	if (myIHaveLifeSteal == true)
	{
		myVitals.IncreaseVital(aLifeStealAmount, enumVitalTypes::eHealth);
	}
}

void Creature::SetLifeSteal(const bool aIHaveLifeSteal)
{
	myIHaveLifeSteal = aIHaveLifeSteal;
}

size_t Creature::GetAttackCount()
{
	return myAttacks.size();
}

void Creature::RecalculateStatBasedActions()
{
	RecalculateAllDamage();
	RecalculateAllVitals();
}

void Creature::RecalculateAllVitals()
{
	for (unsigned int iVital = 0; iVital < static_cast<unsigned int>(enumVitalTypes::enumLength); ++iVital)
	{
		myStatsManager.FindRightVitalCalculation(myVitals.GetVitalStat(static_cast<enumVitalTypes>(iVital)));
	}
}

void Creature::RecalculateAllDamage()
{
	myDamageManager.CalculateAllDamage(myAttacks, myStatsManager, myVitals);
}

float Creature::GetCreatureHitPoints() const
{
	return myVitals.GetVitalValue(enumVitalTypes::eHealth);
}

void Creature::SetStamina(const float aNewStaminaValue)
{
	myVitals.SetVital(aNewStaminaValue, enumVitalTypes::eStamina);
}

void Creature::SetHealth(const float aNewHealthValue)
{
	myVitals.SetVital(aNewHealthValue, enumVitalTypes::eHealth);
}

bool Creature::GetHasEnergy() const
{
	return myVitals.GetVitalState(enumVitalTypes::eStamina);
}

bool Creature::GetIsAlive(const bool aPrintIfDied) const
{

	const bool CurrentAliveState = myVitals.GetVitalState(enumVitalTypes::eHealth);

	if (aPrintIfDied == true)
	{
		if (CurrentAliveState == false)
		{
			if (myBuffCount > 0)
			{
				l1functions::console::PrintToConsole("Killing ", false);
				l1functions::console::PrintToConsole(myNameAndDescription.name, false);
				l1functions::console::PrintToConsole(" has temporarily made you stronger.");
			}
			else
			{
				l1functions::console::PrintToConsole(myNameAndDescription.name, false);
				l1functions::console::PrintToConsole(" has died");
			}
			if (myItemCount > 0)
			{
				l1functions::console::PrintToConsole(myNameAndDescription.name, false);
				l1functions::console::PrintToConsole(" dropped ", false);
				l1functions::console::PrintNumberToConsole(static_cast<int>(myItemCount), false);
				if (myItemCount != 1)
				{
					l1functions::console::PrintToConsole(" items.");
				}
				else
				{
					l1functions::console::PrintToConsole(" item.");
				}
			}
			else
			{
				l1functions::console::ConsoleWhiteSpace();
			}
		}
	}

	return CurrentAliveState;
}

const unsigned int Creature::GetStatValue(const enumStatTypes aStatToCheck) const
{
	return myStatsManager.GetStatValue(aStatToCheck);
}

void Creature::PayForAction(const float aActionCost)
{
	myVitals.ChangeVital(-aActionCost, enumVitalTypes::eStamina);
}
