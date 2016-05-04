#pragma once
#include "DamagePower.h"
#include "Stats\StatsManager.h"
#include "Stats\VitalsManager.h"

class DamageManager
{
public:
	DamageManager();
	~DamageManager();

	void CalculateAllDamage(std::vector<DamagePower>& aAllDamagePowers, StatsManager & aStatsManager, VitalsManager & aVitalsManager);

private:

	void FindRightDamageCalculation(DamagePower & aDamageType, StatsManager & aStatsManager, VitalsManager & aVitalsManager);

	void MagicAttackTypeCalculation(DamagePower & aDamageType, StatsManager & aStats, float aDamageMultiplier);

	void NormalAttackTypeCalculation(DamagePower & aDamageType, StatsManager & aStats, float aDamageMultiplier);

};

