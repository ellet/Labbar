#include "stdafx.h"
#include "KasinoGeneralFunctions.h"

namespace Kasino {
namespace General {

int ThrowD6Dice(const bool aShowEvenNumber)
{
	const int DiceRoll = MyFunctions::Math::SlumpWholeNumber(6);
	std::cout << "Dice rolled is: " << DiceRoll;
	if (aShowEvenNumber == true)
	{
		if (MyFunctions::Math::CheckNumberIfEven(DiceRoll))
		{
			std::cout << " which is even" << std::endl;
		}
		else
		{
			std::cout << " which is uneven" << std::endl;
		}
	}
	else
	{
		std::cout << std::endl;
	}
	return DiceRoll;
}

bool PlayAgainCheck(float & aUserMoney, float & aTableStanding)
{
	const int CurrentTableStandings = Kasino::General::CheckTableStandings(aTableStanding);
	if (CurrentTableStandings == 2 || (aUserMoney <= 0)
		|| CurrentTableStandings == 3)
	{
		return false;
	}

	std::string playAgainQuestion = "Stay and play again?";
	return MyFunctions::Console::AskTrueOrFalse(playAgainQuestion);
}

int CheckTableStandings(float & aTableStanding)
{
	const float CurrentTableStandings = aTableStanding;

	if (MyFunctions::Math::EnforcePositiveNumber(CurrentTableStandings) > Kasino::General::TableToleransLevel)
	{

		if (CurrentTableStandings < 0)
		{
			return 1;
		}
		else
		{
			if (CurrentTableStandings >= Kasino::General::TableKickoutLevel)
			{
				std::cout << "Security comes and gently guide you back to the lobby" << std::endl;
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
	else
	{
		return 0;
	}
}

bool GiveInstructions(std::string aWelcome, std::string aInstructions, float & aTableStanding)
{
	const int CurrentTableStanding = Kasino::General::CheckTableStandings(aTableStanding);
	if (CurrentTableStanding == 2)
	{
		return false;
	}
	else if (CurrentTableStanding == 1)
	{
		std::cout << "Welcome back friend!" << std::endl;
	}
	else if (CurrentTableStanding == 3)
	{
		std::cout << "aaah welcome back, don't the other tables look more interesting." << std::endl;
	}
	else
	{
		std::cout << aWelcome << std::endl;
	}

	if (MyFunctions::Console::AskTrueOrFalse("Do you need instructions how to play"))
	{
		std::cout << "You will be asked how much of your money you are willing to bet. If you win you will be given the amount of money to bet multiplied by the odds, if you lose you will lose the amount you bet." << std::endl << std::endl << aInstructions << std::endl;
		return MyFunctions::Console::AskTrueOrFalse("Would you like to play?");
	}

	return true;
}

void PrintWinOrLose(const float aBetAmount, const float aGameOdds, const bool aUserWin, float &aUserMoney, float &aTableWinnings)
{
	float moneyChange = 0;
	if (aUserWin == true)
	{

		float winAmount = (aBetAmount * aGameOdds);
		moneyChange += winAmount;
		std::cout << "You win " << winAmount << std::endl;
	}
	else
	{
		moneyChange -= aBetAmount;
		std::cout << "You lose " << aBetAmount << std::endl;
	}
	aTableWinnings += moneyChange;
	aUserMoney += moneyChange;
	std::cout << "You now have " << aUserMoney << std::endl << std::endl;

	float const currentTableStandings = aTableWinnings;
	if (currentTableStandings > 0)
	{
		std::cout << "You have won " << currentTableStandings << " at this table" << std::endl;
	}
	else if (currentTableStandings < 0)
	{
		std::cout << "You have losed " << MyFunctions::Math::EnforcePositiveNumber(currentTableStandings) << " at this table" << std::endl;
	}
	
}

float BetMoney(const float aOdds, const float aCurrentMoney)
{
	std::cout << "Odds are: " << aOdds << std::endl;
	std::cout << "You have: " << aCurrentMoney << std::endl;
	const float UserBet = MyFunctions::Console::AskForNumber("How much would you like to bet", "You cant bet a negative amount or money you dont have", 0.0f, aCurrentMoney);
	if (UserBet == aCurrentMoney)
	{
		std::cout << "Player going all in!" << std::endl;
	}
	return UserBet;
}

}
}
