// Kasino1 - Hassardspel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <string>

int SlumpWholeNumber(int aMax);

bool AskTrueOrFalse(std::string aYesNoQuestion);

int AskForNumber(std::string aTextQuestionForNumber, int aMinRange, int aMaxRange);

int AskForNumber(std::string aTextQuestionForNumber, std::string aInvalidInputResponse, int aMinRange, int aMaxRange);

float AskForNumber(std::string aTextQuestionForNumber, float aMinRange, float aMaxRange);

float AskForNumber(std::string aTextQuestionForNumber, std::string aInvalidInputResponse, float aMinRange, float aMaxRange);

void PrintWinOrLose(float aBetAmount, float aGameOdds, bool aUserWin);

float BetMoney(float aOdds, float aCurrentMoney);

bool GiveInstructions(std::string aWelcome, std::string aInstructions);

bool CheckNumberIfEven(int aNumberToCheck);

void GameMenu();

int ThrowD6Dice(bool aShowEvenNumber);

bool PlayAgainCheck();

void GuessNumberGame();

void GuessEvenOrUnevenNumberGame();

void DumpCIN();



float globalUserMoney = 100;

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

	bool tPlayGames = true;
	while (tPlayGames)
	{
		if (globalUserMoney <= 0)
		{
			std::cout << std::endl << "You are out of money" << std::endl << "Security come and throws you out" << std::endl;
			tPlayGames = false;
			system("pause");
		}
		else
		{
			std::string tMenuOptions = "What would you like to do ? \n 1 - Play guess number game \n 2 - Play guess odd or even \n 3 - Leave casino \n";
			int tPlayerGameChoice = AskForNumber(tMenuOptions, 1, 3);
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
				case 3:
				{
					tPlayGames = false;
					std::cout << "Player leaves casino with " << globalUserMoney << " money" << std::endl;
					system("pause");
					break;
				}
				default:
				{
					break;
				}
			}

			std::cout << "You go back to the lobby" << std::endl << std::endl;
		}
	}
}

bool PlayAgainCheck()
{
	if (globalUserMoney <= 0)
	{
		return false;
	}

	std::string tPlayAgainQuestion = "Stay and play again?";
	return AskTrueOrFalse(tPlayAgainQuestion);
}

void GuessNumberGame()
{

	

	bool tPlayAgain = GiveInstructions("Welcome to guess a number table", "Guess a Number between 2-12 then roll a two six sidded dices and compare the results");
	

	std::cout << std::endl;
	std::cout << std::endl;

	

	while (tPlayAgain)
	{
		float tUserBetAmount;
		float tOdds = 2.0f;
		tUserBetAmount = BetMoney(tOdds, globalUserMoney);

		std::cout << std::endl;

		int tUserNumberGuess = AskForNumber("Guess a number between 2 and 12 ", 2, 12);

		std::cout << std::endl;

		std::cout << "Rolling dice " << std::endl << std::endl;


		int tDiceOne = ThrowD6Dice(false);
		int tDiceTwo = ThrowD6Dice(false);
		int tDiceResult = tDiceOne + tDiceTwo;

		std::cout << std::endl;

		std::cout << "You guessed: " << tUserNumberGuess << std::endl;
		std::cout << "Roll Results are: " << tDiceResult << std::endl;

		bool tUserWin;
		if (tUserNumberGuess == tDiceResult)
		{
			std::cout << "You guessed correctly " << std::endl;
			tUserWin = true;
		}
		else
		{
			std::cout << "You guessed wrong " << std::endl << std::endl;
			tUserWin = false;
		}

		PrintWinOrLose(tUserBetAmount, tOdds, tUserWin);

		tPlayAgain= PlayAgainCheck();

	}
}

void GuessEvenOrUnevenNumberGame()
{
	bool tPlayAgain = GiveInstructions("Welcome to guess even or uneven table", "You will guess even or uneven, then you will roll two dice if bought are even or uneven your results will be compared and if you guessed correctly you will win. If you guessed incorrectly or one is even the other uneven you lose.");


	std::cout << std::endl;
	std::cout << std::endl;


	while (tPlayAgain)
	{
		float tUserBetAmount;
		float tOdds = 1.5f;
		tUserBetAmount = BetMoney(tOdds, globalUserMoney);

		std::cout << std::endl;

		int tUserNumberGuess = AskForNumber("Please input 1 for even or 2 for uneven", 1, 2);
		bool tUserEvenGuess = CheckNumberIfEven(tUserNumberGuess);

		std::cout << std::endl;

		std::cout << "Rolling dice " << std::endl << std::endl;


		int tDiceOne = ThrowD6Dice(true);
		int tDiceTwo = ThrowD6Dice(true);
		int tDiceResult = tDiceOne + tDiceTwo;

		bool tDiceOneEven = CheckNumberIfEven(tDiceOne);
		bool tDiceTwoEven = CheckNumberIfEven(tDiceTwo);

		std::cout << "Dices Combined are: " << tDiceResult << std::endl;
		std::cout << std::endl;

		std::string tUserGuessInText;
		if (tUserEvenGuess)
		{
			tUserGuessInText = "Even";
		}
		else
		{
			tUserGuessInText = "Uneven";
		}


		std::cout << "You guessed: " << tUserGuessInText << std::endl;
		
		
		bool tPlayerWin;

		if (tDiceOneEven == tDiceTwoEven)
		{
			if (tDiceOneEven == tUserEvenGuess)
			{
				std::cout << "You guessed correctly " << std::endl;
				tPlayerWin = true;
			}
			else
			{
				std::cout << "You guessed wrong " << std::endl << std::endl;
				tPlayerWin = false;
			}
		}
		else
		{
			std::cout << "Dice are even and uneven player lose" << std::endl;
			tPlayerWin = false;
		}

		PrintWinOrLose(tUserBetAmount, tOdds, tPlayerWin);

		tPlayAgain = PlayAgainCheck();

	}
}

bool CheckNumberIfEven(int aNumberToCheck)
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

bool GiveInstructions(std::string aWelcome ,std::string aInstructions)
{
	std::cout << aWelcome << std::endl;

	if (AskTrueOrFalse("Do you need instructions how to play"))
	{
		std::cout << "You will be asked how much of your money you are willing to bet. If you win you will be given the amount of money to bet multiplied by the odds, if you lose you will lose the amount you bet." << std::endl << std::endl << aInstructions << std::endl;
		return AskTrueOrFalse("Would you like to play?");
	}

	return true;
}

void PrintWinOrLose(float aBetAmount,float aGameOdds,bool aUserWin)
{
	if (aUserWin == true)
	{
		
		float tWinAmount = (aBetAmount * aGameOdds);
		globalUserMoney += tWinAmount;
		std::cout << "You win " << tWinAmount << std::endl;
		std::cout << "You now have " << globalUserMoney << std::endl;
	}
	else
	{
		globalUserMoney -= aBetAmount;
		std::cout << "You lose " << aBetAmount << std::endl;
		std::cout << "You now have " << globalUserMoney << std::endl;
	}
}

bool AskTrueOrFalse(std::string aYesNoQuestion)
{
	bool tWrongUserInput = true;
	do
	{
		std::cout << std::endl;
		std::cout << aYesNoQuestion << " Y/N" << std::endl;

		char tPlayerPromptInput;
		std::cin >> tPlayerPromptInput;

		DumpCIN();

		if (tPlayerPromptInput == 'Y')
		{
			return true;
		}
		else if (tPlayerPromptInput == 'y')
		{
			return true;
		}
		if (tPlayerPromptInput == 'N')
		{
			return false;
		}
		else if (tPlayerPromptInput == 'n')
		{
			return false;
		}
		else
		{
			std::cout << "Invalid Input" << std::endl << std::endl;
		}
	} while (tWrongUserInput);
	return false;
}

int AskForNumber(std::string aTextQuestionForNumber, int aMinRange, int aMaxRange)
{
	int tUserNumberRespons;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> tUserNumberRespons;
		DumpCIN();
		std::cin.clear();
	} while (tUserNumberRespons < aMinRange || tUserNumberRespons > aMaxRange);
	return tUserNumberRespons;
}

int AskForNumber(std::string aTextQuestionForNumber, std::string aInvalidInputResponse, int aMinRange, int aMaxRange)
{
	int tUserNumberRespons;
	bool tCheckForValidInput;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> tUserNumberRespons;
		DumpCIN();
		std::cin.clear();
		if (tUserNumberRespons < aMinRange || tUserNumberRespons > aMaxRange)
		{
			tCheckForValidInput = true;
			std::cout << aInvalidInputResponse << std::endl;
		}
		else
		{
			tCheckForValidInput = false;
		}
	} while (tCheckForValidInput);
	return tUserNumberRespons;
}

float AskForNumber(std::string aTextQuestionForNumber, float aMinRange, float aMaxRange)
{
	float tUserNumberRespons;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> tUserNumberRespons;
		DumpCIN();
		std::cin.clear();
	} while (tUserNumberRespons < aMinRange || tUserNumberRespons > aMaxRange);
	return tUserNumberRespons;
}

float AskForNumber(std::string aTextQuestionForNumber, std::string aInvalidInputResponse, float aMinRange, float aMaxRange)
{
	float tUserNumberRespons;
	bool tCheckForValidInput;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> tUserNumberRespons;
		DumpCIN();
		std::cin.clear();
		if (tUserNumberRespons < aMinRange || tUserNumberRespons > aMaxRange)
		{
			tCheckForValidInput = true;
			std::cout << aInvalidInputResponse << std::endl;
		}
		else
		{
			tCheckForValidInput = false;
		}
	} while (tCheckForValidInput);
	return tUserNumberRespons;
}

float BetMoney(float aOdds, float aCurrentMoney)
{
	std::cout << "Odds are: " << aOdds << std::endl;
	std::cout << "You have: " << aCurrentMoney << std::endl;
	float tUserBet = AskForNumber("How much would you like to bet", "You cant bet a negative amount or money you dont have", 0.0f, aCurrentMoney);
	if (tUserBet == aCurrentMoney)
	{
		std::cout << "Player going all in!" <<  std::endl;
	}
	return tUserBet;
}


int SlumpWholeNumber(int aMax)
{
	int tRandomNumberHolder = rand() % (aMax);
	tRandomNumberHolder += 1;
	return tRandomNumberHolder;
}

int ThrowD6Dice(bool aShowEvenNumber)
{
	int tDiceRoll = SlumpWholeNumber(6);
	std::cout << "You rolled : " << tDiceRoll;
	if (aShowEvenNumber == true)
	{
		if (CheckNumberIfEven(tDiceRoll))
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
	return tDiceRoll;
}

void DumpCIN()
{
	std::cin.sync();
}