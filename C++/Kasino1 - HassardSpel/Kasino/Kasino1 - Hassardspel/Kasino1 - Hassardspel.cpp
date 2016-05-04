// Kasino1 - Hassardspel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>

int SlumpWholeNumber(int sndMax);

int ThrowD6Dice();

bool PlayAgainCheck();

bool mPlayGame = true;

void DumpCIN();

int main()
{
	std::cout << "Guess a Number between 2-12 then roll a two six sidded dices and compare the results" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	srand(static_cast<unsigned int>(time(0)));

	while (mPlayGame)
	{
		int tUserNumberGuess;
		do
		{
			std::cout << "Guess a number between 2 and 12 " << std::endl;
			std::cin >> tUserNumberGuess;
			DumpCIN();
			std::cin.clear();
		} while (tUserNumberGuess < 2 || tUserNumberGuess > 12);


		std::cout << std::endl;

		std::cout << "Rolling dice " << std::endl << std::endl;

		
		int tDiceOne = ThrowD6Dice();
		int tDiceTwo = ThrowD6Dice();
		int tDiceResult = tDiceOne + tDiceTwo;

		std::cout << std::endl;

		std::cout << "You guessed: " << tUserNumberGuess << std::endl;
		std::cout << "Roll Results are: " << tDiceResult << std::endl;
		if (tUserNumberGuess == tDiceResult)
		{
			std::cout << "You guessed correctly " << std::endl;
		}
		else
		{
			std::cout << "You guessed wrong " << std::endl;
		}

		mPlayGame = PlayAgainCheck();
		
	}

	return 0;
}

bool PlayAgainCheck()
{
	bool tWrongUserInput = true;
	do
	{
		std::cout << std::endl;
		std::cout << "Play again? Y/N" << std::endl;

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

int SlumpWholeNumber(int sndMax)
{
	int tRandomNumberHolder = rand() % (sndMax);
	tRandomNumberHolder += 1;
	return tRandomNumberHolder;
}

int ThrowD6Dice()
{
	int tDiceRoll = SlumpWholeNumber(6);
	std::cout << "You rolled : " << tDiceRoll << std::endl;
	return tDiceRoll;
}

void DumpCIN()
{
	std::cin.sync();
}