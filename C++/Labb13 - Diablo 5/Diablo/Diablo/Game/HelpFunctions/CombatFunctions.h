#pragma once
#include "../Classes/Creature.h"
#include "../Classes/Player.h"

namespace combat
{
	
	void Combat(Player & aPlayer, Creature & aEnemy);

	unsigned int CombatMenu(Player & aPlayer, Creature & aEnemy);

}