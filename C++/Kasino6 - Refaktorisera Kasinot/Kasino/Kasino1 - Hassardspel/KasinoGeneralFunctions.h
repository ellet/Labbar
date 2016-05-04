#pragma once
#include "MyGeneralFunctions/l1generallib.h"

namespace Kasino {
namespace General {

const float TableToleransLevel = 1000;

const float TableKickoutLevel = TableToleransLevel * 1.5f;

enum class enumGameTables 
{
	eGuessNumber = 1,
	eGuessEvenOrUneven,
	eRockPaperScissors,
	eDiceBlackJack,
	eRussianRoulette,
	eNormalRoulette,
	eThinkingNumber,
	eGuessMoreOrLess,
	enumLenght
};

enum class enumTableLikeStates
{
	eLike = 1,
	eNeutral,
	eDislike,
	eHate,
	enumLength
};

int ThrowD6Dice(const bool aShowEvenNumber);

bool PlayAgainCheck(float & aUserMoney, float & aTableStanding);

int CheckTableStandings(float & aTableStanding);

void PrintWinOrLose(const float aBetAmount, const float aGameOdds, const bool aUserWin, float &aUserMoney, float &aTableWinnings);

float BetMoney(const float aOdds, const float aCurrentMoney);

bool GiveInstructions(std::string aWelcome, std::string aInstructions, float & aTableStanding);

}
}