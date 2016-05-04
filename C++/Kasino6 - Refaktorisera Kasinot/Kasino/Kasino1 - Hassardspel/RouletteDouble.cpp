#include "stdafx.h"
#include "RouletteDouble.h"

namespace Kasino {
namespace Roullete {
void RoulettePlayDoubleStreet(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(6);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = MyFunctions::Console::AskForNumber("Which row would you like to be your top row? 1 to 11", 1, 11);

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

	std::cout << "You bet a double street on row : " << PlayerBetOn << std::endl;
	std::cout << "Winning row is: " << Kasino::Roullete::General::GetRowFromSquare(BallLandedOn) << std::endl;

	const int RowDifference = PlayerBetOn - Kasino::Roullete::General::GetRowFromSquare(BallLandedOn);

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
}
}
