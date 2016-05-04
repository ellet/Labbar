#include "stdafx.h"
#include "GuessNumber.h"


GuessNumber::GuessNumber()
{
}


GuessNumber::~GuessNumber()
{
}

void GuessNumber::PlayGame(Player & aThePlayer)
{
	bool playAgain = Kasino::General::GiveInstructions("Welcome to guess a number table", "Guess a Number between 2-12 then roll a two six sidded dices and compare the results", myCashFlow.GetTableFeelingsState());


	std::cout << std::endl;
	std::cout << std::endl;



	while (playAgain)
	{
		float userBetAmount;
		const float Odds = 2.0f;
		userBetAmount = Kasino::General::BetMoney(Odds, aThePlayer.GetMoney());

		std::cout << std::endl;

		int userNumberGuess = MyFunctions::Console::AskForNumber("Guess a number between 2 and 12 ", 2, 12);

		std::cout << std::endl;

		std::cout << "Rolling dice " << std::endl << std::endl;


		int diceOne = Kasino::General::ThrowD6Dice(false);
		int diceTwo = Kasino::General::ThrowD6Dice(false);
		int diceResult = diceOne + diceTwo;

		std::cout << std::endl;

		std::cout << "You guessed: " << userNumberGuess << std::endl;
		std::cout << "Roll Results are: " << diceResult << std::endl;

		bool userWin;
		if (userNumberGuess == diceResult)
		{
			std::cout << "You guessed correctly " << std::endl;
			userWin = true;
		}
		else
		{
			std::cout << "You guessed wrong " << std::endl << std::endl;
			userWin = false;
		}

		Kasino::General::PrintWinOrLose(userBetAmount, Odds, userWin, aThePlayer, myCashFlow);

		playAgain = Kasino::General::PlayAgainCheck(aThePlayer, myCashFlow);
	}
}