#include "stdafx.h"
#include "WhatNumberAmIThinkingOf.h"


WhatNumberAmIThinkingOf::WhatNumberAmIThinkingOf()
{
}


WhatNumberAmIThinkingOf::~WhatNumberAmIThinkingOf()
{
}

void WhatNumberAmIThinkingOf::PlayGame(Player & aThePlayer)
{

	bool playAgain = Kasino::General::GiveInstructions("Welcome to think of a number table", "I will think of a number in a really big range then you get as many guesses as you want until either win or give up", myCashFlow.GetTableFeelingsState());


	std::cout << std::endl;
	std::cout << std::endl;



	while (playAgain)
	{
		float userBetAmount;
		const float Odds = 1000.0f;
		const int HighestThinkingNumber = 100000000;
		userBetAmount = Kasino::General::BetMoney(Odds, aThePlayer.GetMoney());

		std::cout << std::endl;

		std::cout << "Im Thinking of a number " << std::endl << std::endl;

		std::cout << std::endl;

		const int DealerThinkingNumber = MyFunctions::Math::SlumpWholeNumber(HighestThinkingNumber);

		int userNumberGuess = MyFunctions::Console::AskForNumber("Guess which between 1 and 1000000 ", 1, HighestThinkingNumber);

		std::cout << std::endl;

		bool playerGiveUp = false;

		while (userNumberGuess != DealerThinkingNumber)
		{
			playerGiveUp = MyFunctions::Console::AskTrueOrFalse("Wrong! give up?");
			if (playerGiveUp)
			{
				break;
			}
			else
			{
				userNumberGuess = MyFunctions::Console::AskForNumber("Guess again then between 1 and 1000000 ", 1, HighestThinkingNumber);
			}
		}


		Kasino::General::PrintWinOrLose(userBetAmount, Odds, !playerGiveUp, aThePlayer, myCashFlow);

		playAgain = Kasino::General::PlayAgainCheck(aThePlayer, myCashFlow);
	}
}