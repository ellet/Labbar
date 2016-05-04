#pragma once
#include <vector>
#include "BaseStat.h"
#include "../DamagePower.h"
#include "BaseStatEnum.h"
#include "VitalStat.h"

class StatsManager
{
public:
	StatsManager();
	~StatsManager();

	void PrintStats() const;

	void ReceiveMainBuffs(const std::vector<Buff> & aVectorOfStatBuffs);

	void AddMainBuffToStat(const Buff aBuffToAdd);

	void AddTempBuffToStat(const Buff aBuffToAdd);

	void SetStat(const unsigned int aValueToSet, const enumStatTypes aStatToSet);

	unsigned int GetStatValue(const enumStatTypes aStatType) const;

	void FindRightVitalCalculation(VitalStat & aVitalStat);

	void TimeCheckTrigger(const unsigned int aTurnCount);

private:

	void ClearAllMainBuffs();

	/*
	Attack Types
	*/

	

	/////////////////////

	/*
	Vital Formulas
	*/
	void CarryLimitFormula(VitalStat & aVitalToSetup);

	void StaminaSetupFormula(VitalStat & aVitalToSetup);

	void HealthSetupFormula(VitalStat & aVitalToSetup);

	void DefenseSetupFormula(VitalStat & aVitalToSetup);

	////////////////////
	void CreateStats();

	std::vector<BaseStat> myStats;
};

