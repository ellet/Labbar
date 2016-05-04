#include "stdafx.h"
#include "EnemyFactory.h"


EnemyFactory::EnemyFactory()
{
	CreateAllCreatureTemplates();
}


EnemyFactory::~EnemyFactory()
{
}

Creature & EnemyFactory::GetNewCreature()
{
	return myCreatureTemplates[0];
}

void EnemyFactory::CreateAllCreatureTemplates()
{
	Creature tempCreature = Creature();

	tempCreature.SetHealth(25.f);

	StatsManager tempStats;

	tempStats.SetStat(3, enumStatTypes::eStrength);
	tempStats.SetStat(4, enumStatTypes::eIntelligens);
	tempStats.SetStat(4, enumStatTypes::eAgility);
	tempStats.SetStat(2, enumStatTypes::eKondition);

	tempCreature.SetAllStats(tempStats);
	myCreatureTemplates.push_back(tempCreature);
}
