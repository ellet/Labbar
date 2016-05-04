#include "stdafx.h"
#include "DiceBlackJackGame.h"

namespace Kasino {
namespace Games {

void DiceBlackJack(float & aUserMoney, float & aTableStanding)
{
	const int GameWinningNumber = 21;

	bool playAgain = Kasino::General::GiveInstructions("Welcome to the Dice Black Jack table", "You and the dealer will roll three dice each, you will then choose you if you want to roll another dice or stop if you go over 21 you lose. after you are done it will be the dealers turn highest number wins none wins incase of a tie.", aTableStanding);


	std::cout << std::endl;
	std::cout << std::endl;



	while (playAgain)
	{
		float userBetAmount;
		const float Odds = 2.0f;
		userBetAmount = Kasino::General::BetMoney(Odds, aUserMoney);


		std::cout << std::endl;

		std::cout << "Rolling starting dice " << std::endl << std::endl;

		std::cout << "Dealer Rolling" << std::endl;
		int diceOne = Kasino::General::ThrowD6Dice(false);
		int diceTwo = Kasino::General::ThrowD6Dice(false);
		int npcDiceResult = diceOne + diceTwo;
		npcDiceResult += Kasino::General::ThrowD6Dice(false);
		std::cout << "Dealer starts at " << npcDiceResult << std::endl << std::endl;

		std::cout << "Player Rolling" << std::endl;
		diceOne = Kasino::General::ThrowD6Dice(false);
		diceTwo = Kasino::General::ThrowD6Dice(false);
		int playerDiceResult = diceOne + diceTwo;
		playerDiceResult += Kasino::General::ThrowD6Dice(false);
		std::cout << "Player starts at " << playerDiceResult << std::endl << std::endl;

		std::cout << std::endl;

		std::cout << "You have " << playerDiceResult << std::endl;
		do
		{

			if (!MyFunctions::Console::AskTrueOrFalse("Would you like to throw another dice?"))
			{
				break;
			}
			else
			{
				playerDiceResult += Kasino::General::ThrowD6Dice(false);
				std::cout << "You have " << playerDiceResult << std::endl;
			}
		} while (playerDiceResult < GameWinningNumber);

		system("pause");
		std::cout << std::endl;
		std::cout << std::endl;

		if (playerDiceResult <= GameWinningNumber)
		{
			std::cout << "Dealer has " << npcDiceResult << std::endl;
			do
			{

				if (npcDiceResult >(GameWinningNumber - 6))
				{
					if (npcDiceResult >= playerDiceResult)
					{
						break;
					}
				}

				npcDiceResult += Kasino::General::ThrowD6Dice(false);
				std::cout << "Dealer has " << npcDiceResult << std::endl;

			} while (npcDiceResult < GameWinningNumber);
		}
		else
		{
			std::cout << "Player over, Dealer stops at " << npcDiceResult << std::endl;
		}

		system("pause");
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "You rolled: " << playerDiceResult << std::endl;
		std::cout << "Dealer rolled: " << npcDiceResult << std::endl;


		if (playerDiceResult != npcDiceResult)
		{
			bool userWin;

			if ((playerDiceResult > npcDiceResult || npcDiceResult > GameWinningNumber)
				&& playerDiceResult <= GameWinningNumber)
			{
				std::cout << "Player wins " << std::endl;
				userWin = true;
			}
			else
			{
				std::cout << "Dealer wins " << std::endl << std::endl;
				userWin = false;
			}
			Kasino::General::PrintWinOrLose(userBetAmount, Odds, userWin, aUserMoney, aTableStanding);
		}
		else
		{
			std::cout << "Tie, none wins" << std::endl;
		}

		playAgain = Kasino::General::PlayAgainCheck(aUserMoney, aTableStanding);
	}
}

}
}
