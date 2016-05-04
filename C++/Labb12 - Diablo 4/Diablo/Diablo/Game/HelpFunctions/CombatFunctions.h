#pragma once
#include "../Classes/Creature.h"

namespace combat
{
	
	void Combat(Creature & aPlayer, Creature & aEnemy);

	unsigned int CombatMenu(Creature & aPlayer, Creature & aEnemy);

}