#include "stdafx.h"
#include "CombatFunctions.h"
#include "HelpFunctions.h"

namespace combat
{

	void Combat(Creature & aPlayer, Creature & aEnemy)
	{
		l1functions::console::ClearScreen();

		l1functions::console::PrintToConsole("combat start");
		l1functions::console::ConsoleWhiteSpace();

		do
		{
			const float DamageDealt = aEnemy.TakeDamage(aPlayer.DealDamage(CombatMenu(aPlayer, aEnemy)));
			aPlayer.DoLifeSteal(DamageDealt);
			system("pause");

			l1functions::console::ConsoleWhiteSpace();
			l1functions::console::ConsoleWhiteSpace();
			
			if (aEnemy.GetIsAlive(false) == true)
			{
				aPlayer.TakeDamage(aEnemy.DealDamage(0));
				system("pause");
			}

			l1functions::console::ConsoleWhiteSpace();
			l1functions::console::ConsoleWhiteSpace();
			
		} while (aPlayer.GetIsAlive(false) == true && aEnemy.GetIsAlive() == true);
		system("pause");
	}

	unsigned int CombatMenu(Creature & aPlayer, Creature & aEnemy)
	{
		aPlayer.PrintHealth();
		aEnemy.PrintHealth();

		l1functions::console::ConsoleWhiteSpace();
		l1functions::console::ConsoleWhiteSpace();

		l1functions::console::PrintToConsole("How would you like to attack?");

		std::vector<std::string> tempPlayerAttack;

		aPlayer.ConstructVectorOfNamesOfAttack(tempPlayerAttack);

		return l1functions::console::input::GivePlayerMenuOptions(tempPlayerAttack);
	}

}