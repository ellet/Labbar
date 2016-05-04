#include "stdafx.h"
#include "RockPaperScissors.h"


RockPaperScissors::RockPaperScissors()
{
}


RockPaperScissors::~RockPaperScissors()
{
}

void RockPaperScissors::PlayGame(Player & aThePlayer)
{
	bool playAgain = Kasino::General::GiveInstructions("Welcome to the rock scissors pappers table", "Choose rock, paper or scissors the dealer will do the same. Rock beats scissors, scissors beat paper, paper beat rocks if there is a tie you will play again until someone wins", myCashFlow.GetTableFeelingsState());


	std::cout << std::endl;
	std::cout << std::endl;



	while (playAgain)
	{
		bool userWin = false;
		float userBetAmount;
		const float Odds = 1.2f;
		userBetAmount = Kasino::General::BetMoney(Odds, aThePlayer.GetMoney());

		std::cout << std::endl;

		bool gameIsTied = true;
		do
		{

			int userTypeChoice = MyFunctions::Console::AskForNumber("Choose: 1 - Rock, 2 - Scissors or 3 - Paper ", 1, 3);

			std::cout << std::endl;

			int npcTypeChoice = MyFunctions::Math::SlumpWholeNumber(3);

			std::cout << std::endl;

			std::cout << "You Choose: " << TranslateNumberToRockPaperScissors(userTypeChoice) << std::endl;
			std::cout << "Dealer Choose: " << TranslateNumberToRockPaperScissors(npcTypeChoice) << std::endl;

			if (userTypeChoice != npcTypeChoice)
			{
				gameIsTied = false;
				const int TypeResults = (userTypeChoice - npcTypeChoice);
				if (TypeResults == -1 || TypeResults == 2)
				{
					std::cout << TranslateNumberToRockPaperScissors(userTypeChoice) << " Beats " << TranslateNumberToRockPaperScissors(npcTypeChoice) << "!" << std::endl;
					std::cout << "Player Wins! " << std::endl;
					userWin = true;
				}
				else
				{
					std::cout << TranslateNumberToRockPaperScissors(npcTypeChoice) << " Beats " << TranslateNumberToRockPaperScissors(userTypeChoice) << "!" << std::endl;
					std::cout << "Dealer Wins! " << std::endl;
					userWin = false;
				}
			}
			else
			{
				gameIsTied = true;
				std::cout << "Game is Tied" << std::endl << std::endl;
				std::cout << "Again!" << std::endl;

			}
		} while (gameIsTied);
		Kasino::General::PrintWinOrLose(userBetAmount, Odds, userWin, aThePlayer, myCashFlow);

		playAgain = Kasino::General::PlayAgainCheck(aThePlayer, myCashFlow);
	}
}

std::string RockPaperScissors::TranslateNumberToRockPaperScissors(const int aChoosenType)
{
	if (aChoosenType == 1)
	{
		return "Rock";
	}
	else if (aChoosenType == 2)
	{
		return "Scissors";
	}
	else
	{
		return "Paper";
	}
}