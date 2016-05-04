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