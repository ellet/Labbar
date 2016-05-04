#include "stdafx.h"
#include "StatsManager.h"
#include "../../HelpFunctions/HelpFunctions.h"
#include "Buff.h"

StatsManager::StatsManager()
{
	CreateStats();
}


StatsManager::~StatsManager()
{
}

void StatsManager::PrintStats() const
{
	std::vector<std::string> myStatPrints;

	for (unsigned int iStat = 0; iStat < myStats.size(); ++iStat)
	{
		myStatPrints.push_back(myStats[iStat].GetPrintStringOfStat());
	}

	l1functions::console::PrintVectorOfStrings(myStatPrints);
}

void StatsManager::ReceiveMainBuffs(const std::vector<Buff>& aVectorOfStatBuffs)
{
	ClearAllMainBuffs();

	

	for (unsigned int iBuff = 0; iBuff < aVectorOfStatBuffs.size(); ++iBuff)
	{
		AddMainBuffToStat(aVectorOfStatBuffs[iBuff]);
	}
}

void StatsManager::AddMainBuffToStat(const Buff aBuffToAdd)
{
	myStats[static_cast<unsigned int>(aBuffToAdd.GetStatType())].AddMainBuff(aBuffToAdd);
}

void StatsManager::AddTempBuffToStat(const Buff aBuffToAdd)
{
	myStats[static_cast<unsigned int>(aBuffToAdd.GetStatType())].AddTempBuff(aBuffToAdd);
}

void StatsManager::SetStat(const unsigned int aValueToSet, const enumStatTypes aStatToSet)
{
	myStats[static_cast<unsigned int>(aStatToSet)].SetStat(aValueToSet);
}

unsigned int StatsManager::GetStatValue(const enumStatTypes aStatType) const
{
	return myStats[static_cast<unsigned int>(aStatType)].GetStatValue();
}

void StatsManager::FindRightVitalCalculation(VitalStat & aVitalStat)
{
	switch (aVitalStat.GetVitalType())
	{
	case enumVitalTypes::eHealth:
		//HealthSetupFormula(aVitalStat);
		break;

	case enumVitalTypes::eStamina:
		StaminaSetupFormula(aVitalStat);
		break;

	case enumVitalTypes::eCarryLimit:
		CarryLimitFormula(aVitalStat);
		break;

	case enumVitalTypes::eDefense:
		DefenseSetupFormula(aVitalStat);
		break;

	default:
		l1functions::console::PrintErrorToConsole("Find right vital formula calculation");
		break;
	}
}

void StatsManager::ClearAllMainBuffs()
{
	for (unsigned int iStat = 0; iStat < myStats.size(); ++iStat)
	{
		myStats[iStat].ClearMainBuffs();
	}
}

void StatsManager::TimeCheckTrigger(const unsigned int aTurnCount)
{
	for (unsigned int iStat = 0; iStat < myStats.size(); ++iStat)
	{
		myStats[iStat].TimeCheckBuffs(aTurnCount);
	}
}


void StatsManager::CarryLimitFormula(VitalStat & aVitalToSetup)
{
	float mySumHolder = 2.f * static_cast<float>(GetStatValue(enumStatTypes::eStrength));

	mySumHolder += static_cast<float>(GetStatValue(enumStatTypes::eKondition));

	aVitalToSetup.SetVital(mySumHolder, true);
}

void StatsManager::StaminaSetupFormula(VitalStat & aVitalToSetup)
{
	float mySumHolder = 15.f * static_cast<float>(GetStatValue(enumStatTypes::eKondition));
	
	aVitalToSetup.SetVital(mySumHolder, true);
}

void StatsManager::HealthSetupFormula(VitalStat & aVitalToSetup)
{
	float mySumHolder = 7.f * static_cast<float>( GetStatValue(enumStatTypes::eKondition));

	mySumHolder += 50.f;
	mySumHolder += static_cast<float>(GetStatValue(enumStatTypes::eStrength));
	
	aVitalToSetup.SetVital(mySumHolder, true);
}

void StatsManager::DefenseSetupFormula(VitalStat & aVitalToSetup)
{
	float mySumHolder = 2.f * static_cast<float>(GetStatValue(enumStatTypes::eStrength));

	mySumHolder *= (static_cast<float>(GetStatValue(enumStatTypes::eAgility) / 10));

	mySumHolder += 5;

	aVitalToSetup.SetVital(mySumHolder, true);
}

void StatsManager::CreateStats()
{
	myStats.clear();
	for (unsigned int iStat = 0; iStat < static_cast<unsigned int>(enumStatTypes::enumLength); ++iStat)
	{
		BaseStat tmpBaseStat;
		tmpBaseStat.SetType(static_cast<enumStatTypes>(iStat));

		myStats.push_back(tmpBaseStat);
	}
}
