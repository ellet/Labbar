#include "stdafx.h"
#include "DamageManager.h"
#include "../HelpFunctions/HelpFunctions.h"

DamageManager::DamageManager()
{
}


DamageManager::~DamageManager()
{
}

void DamageManager::CalculateAllDamage(std::vector<DamagePower>& aAllDamagePowers, StatsManager & aStatsManager, VitalsManager & aVitalsManager)
{
	for (unsigned int iDamage = 0; iDamage < aAllDamagePowers.size(); ++iDamage)
	{
		FindRightDamageCalculation(aAllDamagePowers[iDamage], aStatsManager, aVitalsManager);
	}
}


void DamageManager::FindRightDamageCalculation(DamagePower & aDamageType, StatsManager & aStatsManager, VitalsManager & aVitalsManager)
{
	switch (aDamageType.GetAttackType())
	{
	case enumAttackTypes::eNormalAttack:
		NormalAttackTypeCalculation(aDamageType, aStatsManager, aVitalsManager.GetVitalStat(enumVitalTypes::eHealth).GetVitalValue());
		break;
	case enumAttackTypes::eMagicAttack:
		MagicAttackTypeCalculation(aDamageType, aStatsManager, aVitalsManager.GetVitalStat(enumVitalTypes::eHealth).GetVitalValue());
		break;
	default:
		l1functions::console::PrintErrorToConsole("Attack Type finder out of range");
	}
}

void DamageManager::MagicAttackTypeCalculation(DamagePower & aDamageType, StatsManager & aStats, float aDamageMultiplier)
{
	MinMaxDamage tempDamageHolder;
	tempDamageHolder.maxDamage = (static_cast<float>(aStats.GetStatValue(enumStatTypes::eStrength)) / 40) + (static_cast<float>(aStats.GetStatValue(enumStatTypes::eIntelligens) / 40))
		+ (static_cast<float>(aStats.GetStatValue(enumStatTypes::eAgility)) / 75) * aDamageMultiplier;;
	tempDamageHolder.minDamage = tempDamageHolder.maxDamage * 0.25f;

	aDamageType.SetStaminaCost(2.f);
	aDamageType.SetDamage(tempDamageHolder);
}

void DamageManager::NormalAttackTypeCalculation(DamagePower & aDamageType, StatsManager & aStats, float aDamageMultiplier)
{
	MinMaxDamage tempDamageHolder;
	tempDamageHolder.maxDamage = (aStats.GetStatValue(enumStatTypes::eStrength) * 0.2f) + (aStats.GetStatValue(enumStatTypes::eIntelligens) * 0.8f) + 50.f;
	tempDamageHolder.minDamage = tempDamageHolder.maxDamage * 0.85f +aDamageMultiplier -aDamageMultiplier;

	aDamageType.SetStaminaCost(1.f);
	aDamageType.SetDamage(tempDamageHolder);
}
