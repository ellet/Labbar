#include "stdafx.h"
#include "RouletteSplit.h"

namespace Kasino {
namespace Roullete {
void RoulettePlaySplit(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(2);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerFirstBetOn = MyFunctions::Console::AskForNumber("Which number would you like to be your start number? Bet on a number between 1 to 36", 1, 36);
	int playerSecondBetOn;
	bool invalidSplitInput;
	do
	{
		invalidSplitInput = false;
		playerSecondBetOn = MyFunctions::Console::AskForNumber("Which number would you like to be your second number? Bet on a number between 1 to 36", 1, 36);

		if (PlayerFirstBetOn == playerSecondBetOn)
		{
			std::cout << "You have to choose a different number from your first" << std::endl;
			invalidSplitInput = true;
		}
		else
		{
			const int FirstRow = Kasino::Roullete::General::GetRowFromSquare(PlayerFirstBetOn);
			const int SecondRow = Kasino::Roullete::General::GetRowFromSquare(playerSecondBetOn);
			const int RowDifference = FirstRow - SecondRow;

			const int FirstColumn = Kasino::Roullete::General::GetColumnFromSquare(PlayerFirstBetOn);
			const int SecondColumn = Kasino::Roullete::General::GetColumnFromSquare(playerSecondBetOn);
			const int ColumnDifference = FirstColumn - SecondColumn;

			if ((ColumnDifference == 0 && MyFunctions::Math::EnforcePositiveNumber(RowDifference)) == 1
				|| (MyFunctions::Math::EnforcePositiveNumber(ColumnDifference) == 1 && RowDifference == 0))
			{
				invalidSplitInput = false;
			}
			else
			{
				invalidSplitInput = true;
			}
		}
	} while (invalidSplitInput == true);

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

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
}
}
