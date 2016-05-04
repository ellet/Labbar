// Kasino1 - Hassardspel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <string>


int SlumpWholeNumber(const int aMax);

bool AskTrueOrFalse(const std::string aYesNoQuestion);

int AskForNumber(const std::string aTextQuestionForNumber, const int aMinRange, const int aMaxRange);

int AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const int aMinRange, const int aMaxRange);

float AskForNumber(const std::string aTextQuestionForNumber, const float aMinRange, const float aMaxRange);

float AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const float aMinRange, const float aMaxRange);

std::string TranslateNumberToRockPaperScissors(const int aChoosenType);

float PrintWinOrLose(const float aBetAmount, const float aGameOdds, const bool aUserWin, const int aTableID);

float BetMoney(const float aOdds, const float aCurrentMoney);

bool GiveInstructions(const std::string aWelcome, const std::string aInstructions, const int aCurrentTableID);

float EnforcePositiveNumber(float aNumberToCheck);

int EnforcePositiveNumber(int aNumberToCheck);

bool CheckNumberIfEven(const int aNumberToCheck);

int ThrowD6Dice(const bool aShowEvenNumber);

bool PlayAgainCheck(const int aCurrentTableID);

int CheckTableStandings(const int aTableID);

float CheckTableStandingsValue(const int aTableID);

void GameMenu();

void GuessNumberGame();

void GuessEvenOrUnevenNumberGame();

void RockPaperScissors();

void DiceBlackJack();

void RussianRoulette();

void DumpCIN();



float globalUserMoney = 500;

float globalTableToleransLevel = 1000;

bool globalPlayersIsAlive = true;
bool globalDealerIsAlive = true;

float globalCurrentStandingsGuessNumberTable = 0;
float globalCurrentStandingsGuessEvenOrUnevenTable = 0;
float globalCurrentStandingsRockPaperScissorsTable = 0;
float globalCurrentStandingsDiceBlackJackTable = 0;
float globalCurrentStandingsRussianRoulette = 0;

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	GameMenu();

	return 0;
}

void GameMenu()
{
	std::cout << "You enter the main lobby of the local casino" << std::endl;
	std::cout << "You have: " << globalUserMoney << "money" << std::endl << std::endl;

	bool playGames = true;
	while (playGames)
	{
		if (globalUserMoney <= 0)
		{
			std::cout << std::endl << "You are out of money" << std::endl << "Security come and throws you out" << std::endl;
			playGames = false;
			system("pause");
		}
		else if (globalPlayersIsAlive == false)
		{
			playGames = false;
		}
		else
		{
			std::string tMenuOptions = "What would you like to do ? \n 1 - Play guess number game \n 2 - Play guess odd or even \n 3 - Play Rock Paper Scissors \n 4 - Play Dice Black Jack \n 5 - Play Russian Roulette\n \n 6 - Leave casino";
			int tPlayerGameChoice = AskForNumber(tMenuOptions, 1, 6);
			switch (tPlayerGameChoice)
			{
				case 1:
				{
					GuessNumberGame();
					break;
				}
				case 2:
				{
					GuessEvenOrUnevenNumberGame();
					break;
				}
				case 6:
				{
					playGames = false;
					std::cout << "Player leaves casino with " << globalUserMoney << " money" << std::endl;
					system("pause");
					break;
				}
				case 3:
				{
					RockPaperScissors();
					break;
				}
				case 4:
				{
					DiceBlackJack();
					break;
				}
				case 5:
				{
					RussianRoulette();
					break;
				}
				default:
				{
					break;
				}
			}

			if (globalPlayersIsAlive == true && globalUserMoney > 0)
			{
				std::cout << "You are now back in the lobby" << std::endl << std::endl;
				std::cout << "You have " << globalUserMoney << std::endl << std::endl;
			}
		}
	}
}





void GuessNumberGame()
{

	int myTableID = 0;

	bool playAgain = GiveInstructions("Welcome to guess a number table", "Guess a Number between 2-12 then roll a two six sidded dices and compare the results", myTableID);
	

	std::cout << std::endl;
	std::cout << std::endl;

	

	while (playAgain)
	{
		float userBetAmount;
		float odds = 2.0f;
		userBetAmount = BetMoney(odds, globalUserMoney);

		std::cout << std::endl;

		int userNumberGuess = AskForNumber("Guess a number between 2 and 12 ", 2, 12);

		std::cout << std::endl;

		std::cout << "Rolling dice " << std::endl << std::endl;


		int diceOne = ThrowD6Dice(false);
		int diceTwo = ThrowD6Dice(false);
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

		globalCurrentStandingsGuessNumberTable += PrintWinOrLose(userBetAmount, odds, userWin, myTableID);

		playAgain = PlayAgainCheck(myTableID);
	}
}


void GuessEvenOrUnevenNumberGame()
{
	int myTableID = 1;

	bool playAgain = GiveInstructions("Welcome to guess even or uneven table", "You will guess even or uneven, then you will roll two dice if bought are even or uneven your results will be compared and if you guessed correctly you will win. If you guessed incorrectly or one is even the other uneven you lose.", myTableID);


	std::cout << std::endl;
	std::cout << std::endl;


	while (playAgain)
	{
		float userBetAmount;
		float odds = 1.5f;
		userBetAmount = BetMoney(odds, globalUserMoney);

		std::cout << std::endl;

		int userNumberGuess = AskForNumber("Please input 1 for even or 2 for uneven", 1, 2);
		bool userEvenGuess = CheckNumberIfEven(userNumberGuess);

		std::cout << std::endl;

		std::cout << "Rolling dice " << std::endl << std::endl;


		int diceOne = ThrowD6Dice(true);
		int diceTwo = ThrowD6Dice(true);
		int diceResult = diceOne + diceTwo;

		bool diceOneEven = CheckNumberIfEven(diceOne);
		bool diceTwoEven = CheckNumberIfEven(diceTwo);

		std::cout << "Dices Combined are: " << diceResult << std::endl;
		std::cout << std::endl;

		std::string userGuessInText;
		if (userEvenGuess)
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

		globalCurrentStandingsGuessEvenOrUnevenTable = PrintWinOrLose(userBetAmount, odds, playerWin, myTableID);

		playAgain = PlayAgainCheck(myTableID);

	}
}


void RockPaperScissors()
{

	int myTableID = 2;

	bool playAgain = GiveInstructions("Welcome to the rock scissors pappers table", "Choose rock, paper or scissors the dealer will do the same. Rock beats scissors, scissors beat paper, paper beat rocks if there is a tie you will play again until someone wins", myTableID);


	std::cout << std::endl;
	std::cout << std::endl;



	while (playAgain)
	{
		bool userWin = false;
		float userBetAmount;
		float odds = 1.2f;
		userBetAmount = BetMoney(odds, globalUserMoney);

		std::cout << std::endl;

		bool gameIsTied = true;
		do
		{
			
			int userTypeChoice = AskForNumber("Choose: 1 - Rock, 2 - Scissors or 3 - Paper ", 1, 3);

			std::cout << std::endl;

			int npcTypeChoice = SlumpWholeNumber(3);

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
		globalCurrentStandingsRockPaperScissorsTable += PrintWinOrLose(userBetAmount, odds, userWin, myTableID);

		playAgain = PlayAgainCheck(myTableID);
	}
}


void DiceBlackJack()
{
	const int MyTableID = 3;
	const int GameWinningNumber = 21;

	bool playAgain = GiveInstructions("Welcome to the Dice Black Jack table", "You and the dealer will roll three dice each, you will then choose you if you want to roll another dice or stop if you go over 21 you lose. after you are done it will be the dealers turn highest number wins none wins incase of a tie.", MyTableID);


	std::cout << std::endl;
	std::cout << std::endl;



	while (playAgain)
	{
		float userBetAmount;
		float odds = 2.0f;
		userBetAmount = BetMoney(odds, globalUserMoney);


		std::cout << std::endl;

		std::cout << "Rolling starting dice " << std::endl << std::endl;

		std::cout << "Dealer Rolling" << std::endl;
		int diceOne = ThrowD6Dice(false);
		int diceTwo = ThrowD6Dice(false);
		int npcDiceResult = diceOne + diceTwo;
		npcDiceResult += ThrowD6Dice(false);
		std::cout << "Dealer starts at " << npcDiceResult << std::endl << std::endl;
		
		std::cout << "Player Rolling" << std::endl;
		diceOne = ThrowD6Dice(false);
		diceTwo = ThrowD6Dice(false);
		int playerDiceResult = diceOne + diceTwo;
		playerDiceResult += ThrowD6Dice(false);
		std::cout << "Player starts at " << playerDiceResult << std::endl << std::endl;

		std::cout << std::endl;
		
		std::cout << "You have " << playerDiceResult << std::endl;
		do
		{
			
			if (!AskTrueOrFalse("Would you like to throw another dice?"))
			{
				break;
			}
			else
			{
				playerDiceResult += ThrowD6Dice(false);
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

				npcDiceResult += ThrowD6Dice(false);
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
			globalCurrentStandingsDiceBlackJackTable += PrintWinOrLose(userBetAmount, odds, userWin, MyTableID);
		}
		else
		{
			std::cout << "Tie, none wins" << std::endl;
		}

		playAgain = PlayAgainCheck(MyTableID);
	}
}


void RussianRoulette()
{
	int myTableID = 4;


	if (globalDealerIsAlive)
	{

		//bool playAgain = 
		GiveInstructions("Welcome to the Russian Roulette table", "We will use a 8-chambered revolver. each turn we will spin the barrel and then aim at your own head and fire if you do not you lose the money you bet", myTableID);


		std::cout << std::endl;
		std::cout << std::endl;



		//while (playAgain)
		{
			float userBetAmount;
			float odds = 15.0f;
			userBetAmount = BetMoney(odds, globalUserMoney);

			std::cout << std::endl;

			int bulletLocation; 
			bool userWin = false;

			do
			{
				std::cout << "you spin the barrel" << std::endl;
				bulletLocation = SlumpWholeNumber(8);
				
				if (AskTrueOrFalse("Do you fire the gun"))
				{
					if (bulletLocation == 1)
					{
						globalPlayersIsAlive = false;
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
				bulletLocation = SlumpWholeNumber(8);

				if (bulletLocation == 1)
				{
					globalDealerIsAlive = false;
					std::cout << "Dealer dies" << std::endl;
					userWin = true;
					system("pause");
				}
				else
				{
					std::cout << "dealer is safe, he passes the gun to you" << std::endl;
				}

				

				//playAgain = false;
			} while (globalDealerIsAlive && globalPlayersIsAlive);

			if (userWin || (globalDealerIsAlive && globalPlayersIsAlive))
			{
				globalCurrentStandingsRussianRoulette += PrintWinOrLose(userBetAmount, odds, userWin, myTableID);
				//break;
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




bool PlayAgainCheck(const int aCurrentTableID)
{
	if (CheckTableStandings(aCurrentTableID) == 2 || (globalUserMoney <= 0))
	{
		return false;
	}

	std::string playAgainQuestion = "Stay and play again?";
	return AskTrueOrFalse(playAgainQuestion);
}

bool CheckNumberIfEven(const int aNumberToCheck)
{
	if (aNumberToCheck % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GiveInstructions(std::string aWelcome ,std::string aInstructions, const int aCurrentTableID)
{
	const int CurrentTableStanding = CheckTableStandings(aCurrentTableID);
	if (CurrentTableStanding == 2)
	{
		return false;
	}
	else if (CurrentTableStanding == 1)
	{
		std::cout << "Welcome back friend!" << std::endl;
	}
	else
	{
		std::cout << aWelcome << std::endl;
	}

	if (AskTrueOrFalse("Do you need instructions how to play"))
	{
		std::cout << "You will be asked how much of your money you are willing to bet. If you win you will be given the amount of money to bet multiplied by the odds, if you lose you will lose the amount you bet." << std::endl << std::endl << aInstructions << std::endl;
		return AskTrueOrFalse("Would you like to play?");
	}

	return true;
}

float PrintWinOrLose(const float aBetAmount,const float aGameOdds,const bool aUserWin, const int aTableID)
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
	globalUserMoney += moneyChange;
	std::cout << "You now have " << globalUserMoney << std::endl <<std::endl;

	float const currentTableStandings = (CheckTableStandingsValue(aTableID) + moneyChange);
	if (currentTableStandings > 0)
	{
		std::cout << "You have won " << currentTableStandings << " at this table" << std::endl;
	}
	else if (currentTableStandings < 0)
	{
		std::cout << "You have losed " << EnforcePositiveNumber(currentTableStandings) << " at this table" << std::endl;
	}
	return moneyChange;
}

bool AskTrueOrFalse(const std::string aYesNoQuestion)
{
	bool wrongUserInput = true;
	do
	{
		std::cout << std::endl;
		std::cout << aYesNoQuestion << " Y/N" << std::endl;

		char playerPromptInput;
		std::cin >> playerPromptInput;

		DumpCIN();

		if (playerPromptInput == 'Y')
		{
			return true;
		}
		else if (playerPromptInput == 'y')
		{
			return true;
		}
		if (playerPromptInput == 'N')
		{
			return false;
		}
		else if (playerPromptInput == 'n')
		{
			return false;
		}
		else
		{
			std::cout << "Invalid Input" << std::endl << std::endl;
		}
	} while (wrongUserInput);
	return false;
}

int AskForNumber(const std::string aTextQuestionForNumber, const int aMinRange, const int aMaxRange)
{
	int userNumberRespons;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> userNumberRespons;
		DumpCIN();
		std::cin.clear();
	} while (userNumberRespons < aMinRange || userNumberRespons > aMaxRange);
	return userNumberRespons;
}

int AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const int aMinRange, const int aMaxRange)
{
	int userNumberRespons;
	bool checkForValidInput;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> userNumberRespons;
		DumpCIN();
		std::cin.clear();
		if (userNumberRespons < aMinRange || userNumberRespons > aMaxRange)
		{
			checkForValidInput = true;
			std::cout << aInvalidInputResponse << std::endl;
		}
		else
		{
			checkForValidInput = false;
		}
	} while (checkForValidInput);
	return userNumberRespons;
}

float AskForNumber(const std::string aTextQuestionForNumber, const float aMinRange, const float aMaxRange)
{
	float userNumberRespons;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> userNumberRespons;
		DumpCIN();
		std::cin.clear();
	} while (userNumberRespons < aMinRange || userNumberRespons > aMaxRange);
	return userNumberRespons;
}

float AskForNumber( const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const float aMinRange, const float aMaxRange)
{
	float userNumberRespons;
	bool checkForValidInput;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> userNumberRespons;
		DumpCIN();
		std::cin.clear();
		if (userNumberRespons < aMinRange || userNumberRespons > aMaxRange)
		{
			checkForValidInput = true;
			std::cout << aInvalidInputResponse << std::endl;
		}
		else
		{
			checkForValidInput = false;
		}
	} while (checkForValidInput);
	return userNumberRespons;
}

float BetMoney( const float aOdds, const float aCurrentMoney)
{
	std::cout << "Odds are: " << aOdds << std::endl;
	std::cout << "You have: " << aCurrentMoney << std::endl;
	const float UserBet = AskForNumber("How much would you like to bet", "You cant bet a negative amount or money you dont have", 0.0f, aCurrentMoney);
	if (UserBet == aCurrentMoney)
	{
		std::cout << "Player going all in!" <<  std::endl;
	}
	return UserBet;
}

int CheckTableStandings(const int aTableID)
{
	const float CurrentTableStandings = CheckTableStandingsValue(aTableID);
	
	if (EnforcePositiveNumber(CurrentTableStandings) > globalTableToleransLevel)
	{
		if (CurrentTableStandings < 0)
		{
			return 1;
		}
		else
		{
			std::cout << "Security comes and gently guide you back to the lobby" << std::endl;
			return 2;
		}
	}
	else
	{
		return 0;
	}
}

float CheckTableStandingsValue(const int aTableID)
{
	switch (aTableID)
	{
	case 0:
	{
		return globalCurrentStandingsGuessNumberTable;
		break;
	}
	case 1:
	{
		return globalCurrentStandingsGuessEvenOrUnevenTable;
		break;
	}
	case 2:
	{
		return globalCurrentStandingsRockPaperScissorsTable;
		break;
	}
	case 3:
	{
		return globalCurrentStandingsDiceBlackJackTable;
		break;
	}
	case 4:
	{
		return globalCurrentStandingsRussianRoulette;
		break;
	}
	default:
		std::cout << "ERROR aTableID IS OUT OF RANGE! ERROR" << std::endl;
		system("pause");
		return 0;
		break;
	}
}

std::string TranslateNumberToRockPaperScissors(const int aChoosenType)
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


int SlumpWholeNumber(const int aMax)
{
	int randomNumberHolder = rand() % (aMax);
	randomNumberHolder += 1;
	return randomNumberHolder;
}

int ThrowD6Dice(const bool aShowEvenNumber)
{
	const int DiceRoll = SlumpWholeNumber(6);
	std::cout << "Dice rolled is: " << DiceRoll;
	if (aShowEvenNumber == true)
	{
		if (CheckNumberIfEven(DiceRoll))
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

void DumpCIN()
{
	std::cin.sync();
}

float EnforcePositiveNumber(float aNumberToCheck)
{
	if (aNumberToCheck < 0)
	{
		aNumberToCheck *= -1;
	}
	return aNumberToCheck;
}

int EnforcePositiveNumber(int aNumberToCheck)
{
	if (aNumberToCheck < 0)
	{
		aNumberToCheck *= -1;
	}
	return aNumberToCheck;
}