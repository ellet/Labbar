#include "stdafx.h"
#include "CombatFunctions.h"
#include "HelpFunctions.h"


namespace combat
{

	void Combat(Player & aPlayer, Creature & aEnemy)
	{
		l1functions::console::ClearScreen();

		l1functions::console::PrintToConsole("combat start");
		l1functions::console::ConsoleWhiteSpace();

		do
		{

			const float DamageDealt = aPlayer.PlayerPerformCombatAction(CombatMenu(aPlayer, aEnemy));
			if (DamageDealt > 0.f)
			{
				aEnemy.TakeDamage(DamageDealt);
				aPlayer.GetCreatureInPlayer().DoLifeSteal(DamageDealt);
				system("pause");
			}

			l1functions::console::ConsoleWhiteSpace();
			l1functions::console::ConsoleWhiteSpace();
			
			if (aEnemy.GetIsAlive(false) == true)
			{
				aPlayer.GetCreatureInPlayer().TakeDamage(aEnemy.DealDamage(0));
				system("pause");
			}

			l1functions::console::ConsoleWhiteSpace();
			l1functions::console::ConsoleWhiteSpace();
			
		} while (aPlayer.GetCreatureInPlayer().GetIsAlive(false) == true && aEnemy.GetIsAlive() == true);
		system("pause");
	}

	unsigned int CombatMenu(Player & aPlayer, Creature & aEnemy)
	{
		aPlayer.GetCreatureInPlayer().PrintHealth();
		aEnemy.PrintHealth();

		l1functions::console::ConsoleWhiteSpace();
		l1functions::console::ConsoleWhiteSpace();

		l1functions::console::PrintToConsole("How would you like to attack?");

		std::vector<std::string> tempPlayerAttack;

		aPlayer.PlayerConstructVectorOfAttacks(tempPlayerAttack);

		return l1functions::console::input::GivePlayerMenuOptions(tempPlayerAttack);
	}

}