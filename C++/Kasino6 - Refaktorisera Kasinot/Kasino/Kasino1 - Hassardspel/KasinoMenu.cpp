#include "stdafx.h"
#include "KasinoMenu.h"

namespace Kasino {
void GameMenu()
{
	float userMoney = 500;

	

	bool playersIsAlive = true;
	bool dealerIsAlive = true;

	float currentStandingsGuessNumberTable = 0;
	float currentStandingsGuessEvenOrUnevenTable = 0;
	float currentStandingsRockPaperScissorsTable = 0;
	float currentStandingsDiceBlackJackTable = 0;
	float currentStandingsRussianRoulette = 0;
	float currentStandingsNormalRouletteTable = 0;
	float currentStandingsThinkingNumberTable = 0;


	std::cout << "You enter the main lobby of the local casino" << std::endl;
	std::cout << "You have: " << userMoney << "money" << std::endl << std::endl;

	bool playGames = true;
	while (playGames)
	{
		if (userMoney <= 0)
		{
			std::cout << std::endl << "You are out of money" << std::endl << "Security come and throws you out" << std::endl;
			playGames = false;
			system("pause");
		}
		else if (playersIsAlive == false)
		{
			playGames = false;
		}
		else
		{
			std::string MenuOptions = "What would you like to do ? \n 1 - Play guess number game \n 2 - Play guess odd or even \n 3 - Play Rock Paper Scissors \n 4 - Play Dice Black Jack \n 5 - Play Russian Roulette \n 6 - Play Roullete \n 7 - Play Thinking Number \n 8 - Play Guess more or less \n \n 9 - Leave casino";
			int playerGameChoice = MyFunctions::Console::AskForNumber(MenuOptions, 1, static_cast<int>(Kasino::General::enumGameTables::enumLenght));
			switch (static_cast<Kasino::General::enumGameTables>(playerGameChoice))
			{
			case Kasino::General::enumGameTables::eGuessNumber:
			{
				Kasino::Games::GuessNumberGame(userMoney, currentStandingsGuessNumberTable);
				break;
			}
			case Kasino::General::enumGameTables::eGuessEvenOrUneven:
			{
				Kasino::Games::GuessEvenOrUnevenNumberGame(userMoney, currentStandingsGuessEvenOrUnevenTable);
				break;
			}
			case Kasino::General::enumGameTables::enumLenght:
			{
				playGames = false;
				std::cout << "Player leaves casino with " << userMoney << " money" << std::endl;
				system("pause");
				break;
			}
			case Kasino::General::enumGameTables::eRockPaperScissors:
			{
				Kasino::Games::RockPaperScissors(userMoney, currentStandingsRockPaperScissorsTable);
				break;
			}
			case Kasino::General::enumGameTables::eDiceBlackJack:
			{
				Kasino::Games::DiceBlackJack(userMoney, currentStandingsDiceBlackJackTable);
				break;
			}
			case Kasino::General::enumGameTables::eRussianRoulette:
			{
				Kasino::Games::RussianRoulette(userMoney, currentStandingsRussianRoulette, playersIsAlive, dealerIsAlive);
				break;
			}
			case Kasino::General::enumGameTables::eNormalRoulette:
			{
				Kasino::Games::NormalRoulette(userMoney, currentStandingsNormalRouletteTable);
				break;
			}
			case Kasino::General::enumGameTables::eThinkingNumber:
			{
				Kasino::Games::WhatNumberAmIThinkingOfGameGame(userMoney, currentStandingsThinkingNumberTable);
				break;
			}
			case Kasino::General::enumGameTables::eGuessMoreOrLess:
			{
				Kasino::Games::GuessMoreOrLess(userMoney, currentStandingsThinkingNumberTable);
				break;
			}
			default:
			{
				break;
			}
			}

			if (playersIsAlive == true && userMoney > 0)
			{
				std::cout << "You are now back in the lobby" << std::endl << std::endl;
				std::cout << "You have " << userMoney << std::endl << std::endl;
			}
		}
	}
}
}
