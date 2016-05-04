#include "stdafx.h"
#include "RouletteCorner.h"

namespace Kasino {
namespace Roullete {
void RoulettePlayCorner(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(1);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	int playerBetOn;
	bool checkInvalidCornerStart;
	do
	{
		checkInvalidCornerStart = true;
		playerBetOn = MyFunctions::Console::AskForNumber("Please choose the upper left corner of your corner?", 1, 36);
		if (Kasino::Roullete::General::CheckForRouletteColumn(playerBetOn) == Kasino::Roullete::General::enumRouletteColumn::eRightColumn
			|| Kasino::Roullete::General::GetRowFromSquare(36) == Kasino::Roullete::General::GetRowFromSquare(playerBetOn))
		{
			std::cout << "the corner can't start on the last row or the right most column" << std::endl;
			checkInvalidCornerStart = false;
		}
	} while (checkInvalidCornerStart == false);

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

	std::cout << "You bet a corner that starts on : " << playerBetOn << std::endl;
	std::cout << "Square is: " << BallLandedOn << std::endl;

	const int RowDifference = Kasino::Roullete::General::GetRowFromSquare(playerBetOn) - Kasino::Roullete::General::GetRowFromSquare(BallLandedOn);
	const int CollumnDifference = Kasino::Roullete::General::GetColumnFromSquare(playerBetOn) - Kasino::Roullete::General::GetColumnFromSquare(BallLandedOn);

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
}
}
