#include "stdafx.h"
#include "KasinoClass.h"

KasinoClass::KasinoClass()
{


}


KasinoClass::~KasinoClass()
{


}

void KasinoClass::RunKasino()
{
	myPlayer.TellSetPlayerName();

	std::cout << "You enter the main lobby of the local casino" << std::endl;
	std::cout << "You have: " << myPlayer.GetMoney() << "money" << std::endl << std::endl;

	bool playGames = true;
	while (playGames)
	{
		if (myPlayer.GetMoney() <= 0)
		{
			std::cout << std::endl << "You are out of money" << std::endl << "Security come and throws you out" << std::endl;
			playGames = false;
			system("pause");
		}
		else if (myPlayer.GetAlive() == false)
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
				myGuessNumberGame.PlayGame(myPlayer);
				break;
			}
			case Kasino::General::enumGameTables::eGuessEvenOrUneven:
			{
				myGuessEvenOrUneven.PlayGame(myPlayer);
				break;
			}
			case Kasino::General::enumGameTables::enumLenght:
			{
				playGames = false;
				std::cout << "Player leaves casino with " << myPlayer.GetMoney() << " money" << std::endl;
				system("pause");
				break;
			}
			case Kasino::General::enumGameTables::eRockPaperScissors:
			{
				myRockPaperScissors.PlayGame(myPlayer);
				break;
			}
			case Kasino::General::enumGameTables::eDiceBlackJack:
			{
				myDiceBlackJack.PlayGame(myPlayer);
				break;
			}
			case Kasino::General::enumGameTables::eRussianRoulette:
			{
				myRussianRoulette.PlayGame(myPlayer);
				break;
			}
			case Kasino::General::enumGameTables::eNormalRoulette:
			{
				myNormalRoulette.PlayGame(myPlayer);
				break;
			}
			case Kasino::General::enumGameTables::eThinkingNumber:
			{
				myWhatNumberAmIThinkingOf.PlayGame(myPlayer);
				break;
			}
			case Kasino::General::enumGameTables::eGuessMoreOrLess:
			{
				myGuessMoreOrLess.PlayGame(myPlayer);
				break;
			}
			default:
			{
				break;
			}
			}

			if (myPlayer.GetAlive() == true && myPlayer.GetMoney() > 0)
			{
				std::cout << "You are now back in the lobby" << std::endl << std::endl;
				std::cout << "You have " << myPlayer.GetMoney() << std::endl << std::endl;
			}
		}
	}
}