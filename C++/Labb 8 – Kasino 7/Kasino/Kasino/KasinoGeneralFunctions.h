#pragma once
#include "MyGeneralFunctions/l1generallib.h"
#include "Player.h"
#include "CashFlow.h"
#include "CashFlowEnum.h"

namespace Kasino 
{
	namespace General 
	{

		const float TableToleransLevel = 1000;

		const float TableKickoutLevel = TableToleransLevel * 1.5f;

		enum class enumGameTables {
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


		int ThrowD6Dice(const bool aShowEvenNumber);

		bool PlayAgainCheck(Player & aThePlayer, CashFlow & aCheckCashFlow);

		int CheckTableStandings(float & aTableStanding);

		void PrintWinOrLose(const float aBetAmount, const float aGameOdds, const bool aUserWin, Player &aThePlayer, CashFlow & aTableWinnings);

		float BetMoney(const float aOdds, const float aCurrentMoney);

		bool GiveInstructions(std::string aWelcome, std::string aInstructions, enumTableLikeStates aTableStanding);

	}
}