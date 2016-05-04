#include "stdafx.h"
#include "GuessMoreOrLess.h"


GuessMoreOrLess::GuessMoreOrLess()
{
}


GuessMoreOrLess::~GuessMoreOrLess()
{
}

void GuessMoreOrLess::PlayGame(Player & aThePlayer)
{
	bool playAgain = Kasino::General::GiveInstructions("Welcome " + aThePlayer.GetPlayerName() + ", to guess more or less table", "You will guess even or uneven, then you will roll two dice if bought are even or uneven your results will be compared and if you guessed correctly you will win. If you guessed incorrectly or one is even the other uneven you lose.", myCashFlow.GetTableFeelingsState());


	std::cout << std::endl;
	std::cout << std::endl;


	while (playAgain)
	{
		float userBetAmount;
		const float Odds = 2.f;
		userBetAmount = Kasino::General::BetMoney(Odds, aThePlayer.GetMoney());

		std::cout << std::endl;

		const int BaseNumber = MyFunctions::Math::SlumpNumberBetween(5, 9);

		std::cout << "base number is ";
		std::cout << BaseNumber << std::endl;

		int userNumberGuess = MyFunctions::Console::AskForNumber("Please input 1 for less or 2 for more", 1, 2);
		enumLessAndMore userGuessMoreOrLess = static_cast<enumLessAndMore>(userNumberGuess);

		std::cout << std::endl;

		std::cout << "Rolling dice " << std::endl << std::endl;


		int diceOne = Kasino::General::ThrowD6Dice(true);
		int diceTwo = Kasino::General::ThrowD6Dice(true);
		int diceResult = diceOne + diceTwo;

		std::cout << "base number is ";
		std::cout << BaseNumber << std::endl;

		std::cout << "Dices Combined are: " << diceResult << std::endl;
		std::cout << std::endl;


		//std::cout << "You guessed: " << userGuessInText << std::endl;


		bool playerWin;

		if (userGuessMoreOrLess == enumLessAndMore::eLess)
		{
			if (BaseNumber <= diceResult)
			{
				std::cout << "Dice are more or equal then the base the number player loses" << std::endl;
				playerWin = false;
			}
			else
			{
				std::cout << "Dice are less then the base the number player wins" << std::endl;
				playerWin = true;
			}
		}
		else
		{
			if (BaseNumber <= diceResult)
			{
				std::cout << "Dice are more then the base the number player wins" << std::endl;
				playerWin = true;
			}
			else
			{
				std::cout << "Dice are less or equal then the base the number player loses" << std::endl;
				playerWin = false;
			}
		}

		Kasino::General::PrintWinOrLose(userBetAmount, Odds, playerWin, aThePlayer, myCashFlow);

		playAgain = Kasino::General::PlayAgainCheck(aThePlayer, myCashFlow);

	}
}
