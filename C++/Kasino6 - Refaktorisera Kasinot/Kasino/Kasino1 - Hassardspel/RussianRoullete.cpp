#include "stdafx.h"
#include "RussianRoullete.h"

namespace Kasino {
namespace Games {

void RussianRoulette(float & aUserMoney, float & aTableStanding, bool & aPlayerIsAlive, bool & aDealerIsAlive)
{
	if (aDealerIsAlive)
	{

		bool playAgain = Kasino::General::GiveInstructions("Welcome to the Russian Roulette table", "We will use a 8-chambered revolver. each turn we will spin the barrel and then aim at your own head and fire if you do not you lose the money you bet", aTableStanding);


		std::cout << std::endl;
		std::cout << std::endl;



		if (playAgain)
		{
			float userBetAmount;
			const float Odds = 15.0f;
			userBetAmount = Kasino::General::BetMoney(Odds, aUserMoney);

			std::cout << std::endl;

			int bulletLocation;
			bool userWin = false;

			do
			{
				std::cout << "you spin the barrel" << std::endl;
				bulletLocation = MyFunctions::Math::SlumpWholeNumber(8);

				if (MyFunctions::Console::AskTrueOrFalse("Do you fire the gun"))
				{
					if (bulletLocation == 1)
					{
						aPlayerIsAlive = false;
						std::cout << "The last thing you hear is the click of the gun" << std::endl;
						system("pause");
						break;
					}
					else
					{
						std::cout << "you are safe, you pass the gun to the dealer" << std::endl;
					}
				}
				else
				{
					break;
				}

				std::cout << "the dealer spins the barrel" << std::endl;
				bulletLocation = MyFunctions::Math::SlumpWholeNumber(8);

				if (bulletLocation == 1)
				{
					aDealerIsAlive = false;
					std::cout << "Dealer dies" << std::endl;
					userWin = true;
					system("pause");
				}
				else
				{
					std::cout << "dealer is safe, he passes the gun to you" << std::endl;
				}



			} while (aDealerIsAlive && aPlayerIsAlive);

			if (userWin || (aDealerIsAlive && aPlayerIsAlive))
			{
				Kasino::General::PrintWinOrLose(userBetAmount, Odds, userWin, aUserMoney, aTableStanding);
			}
		}
	}
	else
	{
		std::cout << std::endl;
		std::cout << "The dead dealer is still lying dead on the table. You decide to leave him alone" << std::endl;
		system("pause");
	}
}

}
}
