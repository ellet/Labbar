// Kasino1 - Hassardspel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <string>

enum class enumGameTables {
	eGuessNumber = 1,
	eGuessEvenOrUneven,
	eRockPaperScissors,
	eDiceBlackJack,
	eRussianRoulette,
	eNormalRoulette,
	enumLenght
};

enum class enumRouletteBetTypes {
	eSingle = 1,
	eSplit,
	eStreet,
	eCorner,
	eDoubleStreet,
	eManque,
	ePasse,
	eRedOrBlack,
	EvenorOdd,
	DozenBet,
	Column,
	enumLenght
};

enum class enumRouletteColumn{
	eLeftColumn,
	eMiddleColumn,
	eRightColumn
};

enum class enumRouletteColor{
	eBlack,
	eRed,
	enumLength
};

enum class enumDozenTypes{
	e1_12Premiere,
	e13_24Moyenne,
	e25_36Dernière,
	enumLength
};

int SlumpWholeNumber(const int aMax);

bool AskTrueOrFalse(const std::string aYesNoQuestion);

int AskForNumber(const std::string aTextQuestionForNumber, const int aMinRange, const int aMaxRange);

int AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const int aMinRange, const int aMaxRange);

float AskForNumber(const std::string aTextQuestionForNumber, const float aMinRange, const float aMaxRange);

float AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const float aMinRange, const float aMaxRange);

std::string TranslateNumberToRockPaperScissors(const int aChoosenType);

void PrintWinOrLose(const float aBetAmount, const float aGameOdds, const bool aUserWin, const enumGameTables aTableID);

float BetMoney(const float aOdds, const float aCurrentMoney);

bool GiveInstructions(const std::string aWelcome, const std::string aInstructions, const enumGameTables aCurrentTableID);

float EnforcePositiveNumber(float aNumberToCheck);

int EnforcePositiveNumber(int aNumberToCheck);

bool CheckNumberIfEven(const int aNumberToCheck);

int ThrowD6Dice(const bool aShowEvenNumber);

int RollRoulleteBall();

bool PlayAgainCheck(const enumGameTables aCurrentTableID);

int CheckTableStandings(const enumGameTables aTableID);

float CheckTableStandingsValue(const enumGameTables aTableID);

void ChangeTableStandingsValue(const enumGameTables aTableID, const float aValueToAdd);

float GetRouletteOddsFormula(const int aUserSquaresBetOn);

int GetRowFromSquare(const int aSquareToCheck);

int GetColumnFromSquare(const int aSquareToCheck);

enumRouletteColor GetColorFromSquare(const int aSquareToCheck);

enumDozenTypes GetDozenTypeFromSquare(const int aSquareToCheck);

int GetColorValueFromSquareValue(const int aSquareToCheck);

std::string GetStringRouletteColorFromEnum(const enumRouletteColor aColorToCheck);

std::string GetStringRouletteColumnFromEnum(const enumRouletteColumn aColumnToCheck);

std::string GetStringRouletteOddOrEven(const int aNumberToCheck);

std::string GetStringRouletteDozenType(const enumDozenTypes aTypeToCheck);

enumRouletteColumn CheckForRouletteColumn(const int aSquareToCheckColumn);

void GameMenu();

void GuessNumberGame();

void GuessEvenOrUnevenNumberGame();

void RockPaperScissors();

void DiceBlackJack();

void RussianRoulette();

void NormalRoulette();



bool RouletteMenu(float &abetAmount, float &aBettingOdds, bool &aUserWin);

void RoulettePlaySingle(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlaySplit(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayStreet(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayCorner(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayDoubleStreet(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayManque(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayPasse(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayRedOrBlack(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayEvenOrOdd(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayDozen(float &abetAmount, float &aBettingOdds, bool &aUserWin);
void RoulettePlayColumn(float &abetAmount, float &aBettingOdds, bool &aUserWin);


void DumpCIN();



float globalUserMoney = 500;

float globalTableToleransLevel = 1000;

float globalTableKickOutLevel = globalTableToleransLevel * 1.5f;

bool globalPlayersIsAlive = true;
bool globalDealerIsAlive = true;

float globalCurrentStandingsGuessNumberTable = 0;
float globalCurrentStandingsGuessEvenOrUnevenTable = 0;
float globalCurrentStandingsRockPaperScissorsTable = 0;
float globalCurrentStandingsDiceBlackJackTable = 0;
float globalCurrentStandingsRussianRoulette = 0;
float globalCurrentStandingsNormalRouletteTable = 0;



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
			std::string tMenuOptions = "What would you like to do ? \n 1 - Play guess number game \n 2 - Play guess odd or even \n 3 - Play Rock Paper Scissors \n 4 - Play Dice Black Jack \n 5 - Play Russian Roulette \n 6 - Play Roullete \n \n 7 - Leave casino";
			int playerGameChoice = AskForNumber(tMenuOptions, 1, static_cast<int>(enumGameTables::enumLenght));
			switch (static_cast<enumGameTables>(playerGameChoice))
			{
				case enumGameTables::eGuessNumber:
				{
					GuessNumberGame();
					break;
				}
				case enumGameTables::eGuessEvenOrUneven:
				{
					GuessEvenOrUnevenNumberGame();
					break;
				}
				case enumGameTables::enumLenght:
				{
					playGames = false;
					std::cout << "Player leaves casino with " << globalUserMoney << " money" << std::endl;
					system("pause");
					break;
				}
				case enumGameTables::eRockPaperScissors:
				{
					RockPaperScissors();
					break;
				}
				case enumGameTables::eDiceBlackJack:
				{
					DiceBlackJack();
					break;
				}
				case enumGameTables::eRussianRoulette:
				{
					RussianRoulette();
					break;
				}
				case enumGameTables::eNormalRoulette:
				{
					NormalRoulette();
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

	enumGameTables myTableID = enumGameTables::eGuessNumber;

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

		PrintWinOrLose(userBetAmount, odds, userWin, myTableID);

		playAgain = PlayAgainCheck(myTableID);
	}
}


void GuessEvenOrUnevenNumberGame()
{
	enumGameTables myTableID = enumGameTables::eGuessEvenOrUneven;

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

		PrintWinOrLose(userBetAmount, odds, playerWin, myTableID);

		playAgain = PlayAgainCheck(myTableID);

	}
}


void RockPaperScissors()
{

	enumGameTables myTableID = enumGameTables::eRockPaperScissors;

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
		PrintWinOrLose(userBetAmount, odds, userWin, myTableID);

		playAgain = PlayAgainCheck(myTableID);
	}
}


void DiceBlackJack()
{
	const enumGameTables MyTableID = enumGameTables::eDiceBlackJack;
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
			PrintWinOrLose(userBetAmount, odds, userWin, MyTableID);
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
	enumGameTables myTableID = enumGameTables::eRussianRoulette;


	if (globalDealerIsAlive)
	{

		bool playAgain = GiveInstructions("Welcome to the Russian Roulette table", "We will use a 8-chambered revolver. each turn we will spin the barrel and then aim at your own head and fire if you do not you lose the money you bet", myTableID);


		std::cout << std::endl;
		std::cout << std::endl;



		if (playAgain)
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

				

			} while (globalDealerIsAlive && globalPlayersIsAlive);

			if (userWin || (globalDealerIsAlive && globalPlayersIsAlive))
			{
				PrintWinOrLose(userBetAmount, odds, userWin, myTableID);
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




void NormalRoulette()
{
	enumGameTables myTableID = enumGameTables::eNormalRoulette;

	bool playAgain = GiveInstructions("Welcome to roulette table", "straight(or Single)a single number bet.The chip is placed entirely on the middle of a number square. Split a bet on two adjoining numbers, either on the vertical or horizontal(as in 14 - 17 or 8 - 9).The chip is placed on the line between these numbers. Street a bet on three numbers on a single horizontal line.The chip is placed on the edge of the line of a number at the end of the line(either the left or the right, depending on the layout). Corner(or Square) a bet on four numbers in a square layout(as in 11 - 12 - 14 - 15).The chip is placed at the horizontal and vertical intersection of the lines between the four numbers. Six line(or Double Street) a bet on two adjoining streets, with the chip placed at the corresponding intersection, as if in between where two street bets would be placed. Trio a bet on the intersecting point between 0, 1 and 2, or 0, 2 and 3 (single - zero layout only). Basket(or the first four) (non - square corner) a bet on 0, 1, 2, and 3 (single - zero layout only). Basket a bet on 0, 1, and 2; 0, 00, and 2; or 00, 2, and 3 (double - zero layout only).The chip is placed at the intersection of the three desired numbers. Top line a bet on 0, 00, 1, 2, and 3 (double - zero layout only).The chip is placed either at the corner of 0 and 1, or the corner of 00 and 3. 1 to 18 (Manque) a bet on one of the first low eighteen numbers coming up. 19 to 36 (Passe) a bet on one of the latter high eighteen numbers coming up. Red or black(Rouge ou Noir) a bet on which color the roulette wheel will show. Even or odd(Pair ou Impair) a bet on an even or odd nonzero number. Dozen bets a bet on the first(1 - 12, Premiere douzaine(P12)), second(13 - 24, Moyenne douzaine(M12)), or third group(25 - 36, Dernière douzaine(D12)) of twelve numbers. Column bets a bet on all 12 numbers on any of the three vertical lines(such as 1 - 4 - 7 - 10 on down to 34).The chip is placed on the space below the final number in this sequence.", myTableID);

	std::cout << std::endl;
	std::cout << std::endl;



	while (playAgain)
	{
		float userBetAmount;
		float odds;
		bool userWin;
		if (RouletteMenu(userBetAmount, odds, userWin))
		{
			PrintWinOrLose(userBetAmount, odds, userWin, myTableID);
			
			playAgain = PlayAgainCheck(myTableID);
		}
		else
		{
			playAgain = false;
		}
		
	}
}


bool RouletteMenu(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	std::string tMenuOptions = "How would you like to bet? \n 1 - Single \n 2 - Split \n 3 - Street \n 4 - Corner \n 5 - Double Street \n 6 - 1-18-Manque \n 7 - 19-36-Passe \n 8 - Red or Black \n 9 - Even or Odd \n 10 - Dozen bet, \n 11 - Collumn bet \n \n 12 - Leave Roulette Table";
	int playerBettingChoice = AskForNumber(tMenuOptions, 1, static_cast<int>(enumRouletteBetTypes::enumLenght));
	switch (static_cast<enumRouletteBetTypes>(playerBettingChoice))
	{
		case enumRouletteBetTypes::eSingle:
		{
			RoulettePlaySingle(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::eSplit:
		{
			RoulettePlaySplit(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::eStreet:
		{
			RoulettePlayStreet(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::eCorner:
		{
			RoulettePlayCorner(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::eDoubleStreet:
		{
			RoulettePlayDoubleStreet(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::eManque:
		{
			RoulettePlayManque(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::ePasse:
		{
			RoulettePlayPasse(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::eRedOrBlack:
		{
			RoulettePlayRedOrBlack (abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::EvenorOdd:
		{
			RoulettePlayEvenOrOdd(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::DozenBet:
		{
			RoulettePlayDozen(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::Column:
		{
			RoulettePlayColumn(abetAmount, aBettingOdds, aUserWin);
			break;
		}
		case enumRouletteBetTypes::enumLenght:
		{
			std::cout << "Player Leaves Table" << std::endl;
			return false;
			break;
		}
		default:
		{
			std::cout << "ERROR Betting out of ID range" << std::endl;
			break;
		}
	}
	return true;
}


void RoulettePlaySingle(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(1);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = AskForNumber("Which number would you like to bet on? Bet on a number between 0 to 36", 0, 36);

	const int BallLandedOn = RollRoulleteBall();
	
	std::cout << "You bet on : " << PlayerBetOn << std::endl;
	std::cout << "Results are: " << BallLandedOn << std::endl;
	if (BallLandedOn == PlayerBetOn)
	{
		std::cout << "Player wins!" << std::endl;
		aUserWin = true;
	}
	else
	{
		std::cout << "Player loses" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlaySplit(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(2);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;
	
	const int PlayerFirstBetOn = AskForNumber("Which number would you like to be your start number? Bet on a number between 1 to 36", 1, 36);
	int playerSecondBetOn;
	bool invalidSplitInput;
	do
	{
		invalidSplitInput = false;
		playerSecondBetOn = AskForNumber("Which number would you like to be your second number? Bet on a number between 1 to 36", 1, 36);

		if (PlayerFirstBetOn == playerSecondBetOn)
		{
			std::cout << "You have to choose a different number from your first" << std::endl;
			invalidSplitInput = true;
		}
		else
		{
			const int FirstRow = GetRowFromSquare(PlayerFirstBetOn);
			const int SecondRow = GetRowFromSquare(playerSecondBetOn);
			const int RowDifference = FirstRow - SecondRow;
			
			const int FirstColumn = GetColumnFromSquare(PlayerFirstBetOn);
			const int SecondColumn = GetColumnFromSquare(playerSecondBetOn);
			const int ColumnDifference = FirstColumn - SecondColumn;

			if ((ColumnDifference == 0 && EnforcePositiveNumber(RowDifference)) == 1
				|| (EnforcePositiveNumber(ColumnDifference) == 1 && RowDifference == 0))
			{
				invalidSplitInput = false;
			}
			else
			{
				invalidSplitInput = true;
			}
		}
	} while (invalidSplitInput == true);

	const int BallLandedOn = RollRoulleteBall();

	std::cout << "You bet on : " << PlayerFirstBetOn << std::endl;
	std::cout << "You bet on : " << playerSecondBetOn << std::endl;
	std::cout << "Results are: " << BallLandedOn << std::endl;

	if (BallLandedOn != 0)
	{
		if (BallLandedOn == PlayerFirstBetOn || BallLandedOn == playerSecondBetOn)
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayStreet(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(3);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = AskForNumber("Which row would you like to a street on? 1 to 12", 1, 12);

	const int BallLandedOn = RollRoulleteBall();

	std::cout << "You bet a street on row : " << PlayerBetOn << std::endl;
	std::cout << "Winning row is: " << GetRowFromSquare(BallLandedOn) << std::endl;

	if (BallLandedOn != 0)
	{
		if (PlayerBetOn == GetRowFromSquare(BallLandedOn))
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayCorner(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(1);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	int playerBetOn;
	bool checkInvalidCornerStart;
	do
	{
		checkInvalidCornerStart = true;
		playerBetOn = AskForNumber("Please choose the upper left corner of your corner?", 1, 36);
		if (CheckForRouletteColumn(playerBetOn) == enumRouletteColumn::eRightColumn
			|| GetRowFromSquare(36) == GetRowFromSquare(playerBetOn))
		{
			std::cout << "the corner can't start on the last row or the right most column" << std::endl;
			checkInvalidCornerStart = false;
		}
	} while (checkInvalidCornerStart == false);

	const int BallLandedOn = RollRoulleteBall();

	std::cout << "You bet a corner that starts on : " << playerBetOn << std::endl;
	std::cout << "Square is: " << BallLandedOn << std::endl;

	const int RowDifference = GetRowFromSquare(playerBetOn) - GetRowFromSquare(BallLandedOn);
	const int CollumnDifference = GetColumnFromSquare(playerBetOn) - GetColumnFromSquare(BallLandedOn);
	
	if (BallLandedOn != 0)
	{
		if ((RowDifference == 0 || RowDifference == -1)
			&& (CollumnDifference == 0 || CollumnDifference == -1))
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "Player loses" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayDoubleStreet(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(6);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = AskForNumber("Which row would you like to be your top row? 1 to 11", 1, 11);

	const int BallLandedOn = RollRoulleteBall();

	std::cout << "You bet a double street on row : " << PlayerBetOn << std::endl;
	std::cout << "Winning row is: " << GetRowFromSquare(BallLandedOn) << std::endl;

	const int RowDifference = PlayerBetOn - GetRowFromSquare(BallLandedOn);

	if (BallLandedOn != 0)
	{
		if (RowDifference == 0 || RowDifference == -1)
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayManque(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(18);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int BallLandedOn = RollRoulleteBall();

	std::cout << "You bet between 1 and 18: "<< std::endl;
	std::cout << "Results are: " << BallLandedOn << std::endl;
	
	if (BallLandedOn != 0)
	{
		if (BallLandedOn >= 1 && BallLandedOn <= 18)
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayPasse(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(18);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int BallLandedOn = RollRoulleteBall();

	std::cout << "You bet between 18 and 36: " << std::endl;
	std::cout << "Results are: " << BallLandedOn << std::endl;
	
	if (BallLandedOn != 0)
	{
		if (BallLandedOn >= 18 && BallLandedOn <= 36)
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayRedOrBlack(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(18);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = AskForNumber("Which color would you like to bet on? 1 - Black, 2 - Red", 1, 2) - 1;

	const int BallLandedOn = RollRoulleteBall();

	const enumRouletteColor BallColor = GetColorFromSquare(BallLandedOn);
	const enumRouletteColor PlayerColor = static_cast<enumRouletteColor>(PlayerBetOn);

	std::cout << "You bet on : " << GetStringRouletteColorFromEnum(PlayerColor) << std::endl;
	std::cout << "Results are: " <<  GetStringRouletteColorFromEnum(BallColor) << std::endl;

	if (BallLandedOn != 0)
	{
		if (PlayerColor == BallColor)
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayEvenOrOdd(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(18);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = AskForNumber("Which color would you like to bet on? 1 - Odd, 2 - Even", 1, 2);

	const int BallLandedOn = RollRoulleteBall();

	std::cout << "You bet on : " << GetStringRouletteOddOrEven(PlayerBetOn) << std::endl;
	std::cout << "Results are: " << GetStringRouletteOddOrEven(BallLandedOn) << std::endl;

	if (BallLandedOn != 0)
	{
		if (CheckNumberIfEven(PlayerBetOn) == CheckNumberIfEven(BallLandedOn))
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayDozen(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(12);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = AskForNumber("Which set of dozen would you like to bet on? 1 - 1-12, 2 - 13-24, 3 - 25-36", 1, 3) - 1;

	const int BallLandedOn = RollRoulleteBall();

	const enumDozenTypes BallDozenType = GetDozenTypeFromSquare(BallLandedOn);
	const enumDozenTypes PlayerDozenType = static_cast<enumDozenTypes>(PlayerBetOn);

	std::cout << "You bet on : " << GetStringRouletteDozenType(PlayerDozenType) << std::endl;
	std::cout << "Results are: " << GetStringRouletteDozenType(BallDozenType) << std::endl;
	
	if (BallLandedOn != 0)
	{
		if (PlayerDozenType == BallDozenType)
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}

void RoulettePlayColumn(float &abetAmount, float &aBettingOdds, bool &aUserWin)
{
	aBettingOdds = GetRouletteOddsFormula(12);
	abetAmount = BetMoney(aBettingOdds, globalUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = AskForNumber("Which column would you like bet on? 1 to 3", 1, 3)-1;

	const int BallLandedOn = RollRoulleteBall();

	const enumRouletteColumn BallColumn = CheckForRouletteColumn(BallLandedOn);
	const enumRouletteColumn PlayerColumn = static_cast<enumRouletteColumn>(PlayerBetOn);

	std::cout << "You bet on column : " << GetStringRouletteColumnFromEnum(PlayerColumn) << std::endl;
	std::cout << "Winning row is: " << GetStringRouletteColumnFromEnum(BallColumn) << std::endl;

	if (BallLandedOn != 0)
	{
		if (BallColumn == PlayerColumn)
		{
			std::cout << "Player wins!" << std::endl;
			aUserWin = true;
		}
		else
		{
			std::cout << "Player loses" << std::endl << std::endl;
			aUserWin = false;
		}
	}
	else
	{
		std::cout << "0 is auto lose" << std::endl << std::endl;
		aUserWin = false;
	}
}



bool PlayAgainCheck(const enumGameTables aCurrentTableID)
{
	const int CurrentTableStandings = CheckTableStandings(aCurrentTableID);
	if (CurrentTableStandings == 2 || (globalUserMoney <= 0)
		|| CurrentTableStandings == 3)
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

bool GiveInstructions(std::string aWelcome ,std::string aInstructions, const enumGameTables aCurrentTableID)
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
	else if (CurrentTableStanding == 3)
	{
		std::cout << "aaah welcome back, don't the other tables look more interesting." << std::endl;
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

void PrintWinOrLose(const float aBetAmount,const float aGameOdds,const bool aUserWin, const enumGameTables aTableID)
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
	ChangeTableStandingsValue(aTableID, moneyChange);
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

int CheckTableStandings(const enumGameTables aTableID)
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
			if (CurrentTableStandings >= globalTableKickOutLevel)
			{
				std::cout << "Security comes and gently guide you back to the lobby" << std::endl;
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
	else
	{
		return 0;
	}
}

float CheckTableStandingsValue(const enumGameTables aTableID)
{
	switch (aTableID)
	{
	case enumGameTables::eGuessNumber:
	{
		return globalCurrentStandingsGuessNumberTable;
		break;
	}
	case enumGameTables::eGuessEvenOrUneven:
	{
		return globalCurrentStandingsGuessEvenOrUnevenTable;
		break;
	}
	case enumGameTables::eRockPaperScissors:
	{
		return globalCurrentStandingsRockPaperScissorsTable;
		break;
	}
	case enumGameTables::eDiceBlackJack:
	{
		return globalCurrentStandingsDiceBlackJackTable;
		break;
	}
	case enumGameTables::eRussianRoulette:
	{
		return globalCurrentStandingsRussianRoulette;
		break;
	}
	case enumGameTables::eNormalRoulette:
	{
		return globalCurrentStandingsNormalRouletteTable;
		break;
	}
	default:
		std::cout << "ERROR aTableID IS OUT OF RANGE! ERROR" << std::endl;
		system("pause");
		return 0;
		break;
	}
}

void ChangeTableStandingsValue(const enumGameTables aTableID, const float aValueToAdd)
{
	switch (aTableID)
	{
	case enumGameTables::eGuessNumber:
	{
		globalCurrentStandingsGuessNumberTable += aValueToAdd;
		break;
	}
	case enumGameTables::eGuessEvenOrUneven:
	{
		globalCurrentStandingsGuessEvenOrUnevenTable += aValueToAdd;
		break;
	}
	case enumGameTables::eRockPaperScissors:
	{
		globalCurrentStandingsRockPaperScissorsTable += aValueToAdd;
		break;
	}
	case enumGameTables::eDiceBlackJack:
	{
		globalCurrentStandingsDiceBlackJackTable += aValueToAdd;
		break;
	}
	case enumGameTables::eRussianRoulette:
	{
		globalCurrentStandingsRussianRoulette += aValueToAdd;
		break;
	}
	case enumGameTables::eNormalRoulette:
	{
		globalCurrentStandingsNormalRouletteTable += aValueToAdd;
		break;
	}
	default:
		std::cout << "ERROR aTableID IS OUT OF RANGE! ERROR" << std::endl;
		system("pause");
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

float GetRouletteOddsFormula(const int aUserSquaresBetOn)
{
	return ((36.0f / aUserSquaresBetOn) - 1.0f);
}

enumRouletteColumn CheckForRouletteColumn(const int aSquareToCheckColumn)
{
	switch (GetColumnFromSquare(aSquareToCheckColumn))
	{
		case 3:
		{
			return enumRouletteColumn::eRightColumn;
			break;
		}
		case 1:
		{
			return enumRouletteColumn::eLeftColumn;
			break;
		}
		case 2:
		{
			return enumRouletteColumn::eMiddleColumn;
			break;
		}
		default:
		{
			std::cout << "Column Checker FUCKED UP" << std::endl;
			return enumRouletteColumn::eMiddleColumn;
			break;
		}
	}
}

int GetRowFromSquare(const int aSquareToCheck)
{
	if (aSquareToCheck == 0)
	{
		return 0;
	}
	else
	{
		return ((aSquareToCheck - 1) / 3) + 1;
	}
}

int GetColumnFromSquare(const int aSquareToCheck)
{
	if (aSquareToCheck == 0)
	{
		return 0;
	}
	return ((aSquareToCheck - 1) % 3) + 1;
}

enumDozenTypes GetDozenTypeFromSquare(const int aSquareToCheck)
{
	if (aSquareToCheck >= 1 && aSquareToCheck <= 12)
	{
		return enumDozenTypes::e1_12Premiere;
	}
	else if (aSquareToCheck >= 13 && aSquareToCheck <= 24)
	{
		return enumDozenTypes::e13_24Moyenne;
	}
	if (aSquareToCheck >= 25 && aSquareToCheck <= 36)
	{
		return enumDozenTypes::e25_36Dernière;
	}
	else
	{
		std::cout << "DOZEN FROM SQUARE FUKKEN BROKEN" << std::endl;
		return enumDozenTypes::enumLength;
	}
}

enumRouletteColor GetColorFromSquare(const int aSquareToCheck)
{
	if (aSquareToCheck == 0)
	{
		return enumRouletteColor::enumLength;
	}
	else if ((aSquareToCheck >= 1 && aSquareToCheck <= 10) || (aSquareToCheck >= 21 && aSquareToCheck <= 28))
	{
		if (CheckNumberIfEven(aSquareToCheck))
		{
			return enumRouletteColor::eBlack;
		}
		else
		{
			return enumRouletteColor::eRed;
		}
	}
	else
	{
		if (CheckNumberIfEven(aSquareToCheck))
		{
			return enumRouletteColor::eRed;
		}
		else
		{
			return enumRouletteColor::eBlack;
		}

	}
}

std::string GetStringRouletteColorFromEnum(const enumRouletteColor aColorToCheck)
{
	if (aColorToCheck == enumRouletteColor::eBlack)
	{
		return "Black";
	}
	else if (aColorToCheck == enumRouletteColor::eRed)
	{
		return "Red";
	}
	else
	{
		return "ERROR COLOR FUKKEN BROKEN";
	}
}

std::string GetStringRouletteColumnFromEnum(const enumRouletteColumn aColumnToCheck)
{
	if (aColumnToCheck == enumRouletteColumn::eLeftColumn)
	{
		return "Left Column";
	}
	else if (aColumnToCheck == enumRouletteColumn::eRightColumn)
	{
		return "Right Column";
	}
	if (aColumnToCheck == enumRouletteColumn::eMiddleColumn)
	{
		return "Middle Column";
	}
	else
	{
		return "ERROR COLUMN FUKKEN BROKEN";
	}
}

std::string GetStringRouletteOddOrEven(const int aNumberToCheck)
{
	if ((aNumberToCheck % 2) == 0)
	{
		return "Even";
	}
	else
	{
		return "Odd";
	}
}

std::string GetStringRouletteDozenType(const enumDozenTypes aTypeToCheck)
{
	if (aTypeToCheck == enumDozenTypes::e1_12Premiere)
	{
		return "1-12 Premiere";
	}
	else if (aTypeToCheck == enumDozenTypes::e13_24Moyenne)
	{
		return "13-24 Moeyenne";
	}
	else if (aTypeToCheck == enumDozenTypes::e25_36Dernière)
	{
		return "25-36 Dernière";
	}
	else
	{
		return "ERROR DOZEN TYPE FUKKEN BROKEN";
	}
}

int GetColorValueFromSquareValue(const int aSquareToCheck)
{
	return static_cast<int>(GetColorFromSquare(aSquareToCheck));
}

int RollRoulleteBall()
{
	std::cout << "Wheel is spinning " << std::endl;
	system("pause");
	std::cout << "Wheel is spinning " << std::endl;
	system("pause");
	std::cout << "Wheel is stopping!" << std::endl;
	system("pause");

	std::cout << std::endl;
	std::cout << std::endl;

	int ballLandedOn = (rand() % (37));
	if (ballLandedOn != 0)
	{
		ballLandedOn -= 1;
	}
	std::cout << "The number is: " << ballLandedOn << std::endl;
	std::cout << "The number is: " << GetStringRouletteOddOrEven(ballLandedOn) << std::endl;
	std::cout << "The row is: " << GetRowFromSquare(ballLandedOn) << std::endl;
	std::cout << "The Dozen is: " << GetStringRouletteDozenType(GetDozenTypeFromSquare(ballLandedOn)) << std::endl;
	std::cout << "The color is: " << GetStringRouletteColorFromEnum(GetColorFromSquare(ballLandedOn)) << std::endl;
	std::cout << "The column is: " << GetStringRouletteColumnFromEnum(CheckForRouletteColumn(ballLandedOn)) <<std::endl;

	std::cout << std::endl;
	return ballLandedOn;
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