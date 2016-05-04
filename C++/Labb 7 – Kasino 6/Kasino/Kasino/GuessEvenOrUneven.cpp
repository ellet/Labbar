#include "stdafx.h"
#include "GuessEvenOrUneven.h"


GuessEvenOrUneven::GuessEvenOrUneven()
{
}


GuessEvenOrUneven::~GuessEvenOrUneven()
{
}

void GuessEvenOrUneven::PlayGame(Player & aThePlayer)
{
	bool playAgain = Kasino::General::GiveInstructions("Welcome to guess even or uneven table", "You will guess even or uneven, then you will roll two dice if bought are even or uneven your results will be compared and if you guessed correctly you will win. If you guessed incorrectly or one is even the other uneven you lose.", myCashFlow.GetTableFeelingsState());


	std::cout << std::endl;
	std::cout << std::endl;


	while (playAgain)
	{
		float userBetAmount;
		const float Odds = 1.5f;
		userBetAmount = Kasino::General::BetMoney(Odds, aThePlayer.GetMoney());

		std::cout << std::endl;

		int userNumberGuess = MyFunctions::Console::AskForNumber("Please input 1 for even or 2 for uneven", 1, 2);
		bool userEvenGuess = MyFunctions::Math::CheckNumberIfEven(userNumberGuess + 1);

		std::cout << std::endl;

		std::cout << "Rolling dice " << std::endl << std::endl;


		int diceOne = Kasino::General::ThrowD6Dice(true);
		int diceTwo = Kasino::General::ThrowD6Dice(true);
		int diceResult = diceOne + diceTwo;

		bool diceOneEven = MyFunctions::Math::CheckNumberIfEven(diceOne);
		bool diceTwoEven = MyFunctions::Math::CheckNumberIfEven(diceTwo);

		std::cout << "Dices Combined are: " << diceResult << std::endl;
		std::cout << std::endl;

		std::string userGuessInText;
		if (userEvenGuess == true)
		{
			userGuessInText = "Even";
		}
		else
		{
			userGuessInText = "Uneven";
		}


		std::cout << "You guessed: " << userGuessInText << std::endl;


		bool playerWin;

		if (diceOneEven == diceTwoEven)
		{
			if (diceOneEven == userEvenGuess)
			{
				std::cout << "You guessed correctly " << std::endl;
				playerWin = true;
			}
			else
			{
				std::cout << "You guessed wrong " << std::endl << std::endl;
				playerWin = false;
			}
		}
		else
		{
			std::cout << "Dice are even and uneven player lose" << std::endl;
			playerWin = false;
		}

		Kasino::General::PrintWinOrLose(userBetAmount, Odds, playerWin, aThePlayer, myCashFlow);

		playAgain = Kasino::General::PlayAgainCheck(aThePlayer, myCashFlow);
	}
}