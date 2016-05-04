#include "stdafx.h"
#include "RouletteStreet.h"

namespace Kasino {
namespace Roullete {
void RoulettePlayStreet(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(3);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = MyFunctions::Console::AskForNumber("Which row would you like to a street on? 1 to 12", 1, 12);

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

	std::cout << "You bet a street on row : " << PlayerBetOn << std::endl;
	std::cout << "Winning row is: " << Kasino::Roullete::General::GetRowFromSquare(BallLandedOn) << std::endl;

	if (BallLandedOn != 0)
	{
		if (PlayerBetOn == Kasino::Roullete::General::GetRowFromSquare(BallLandedOn))
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
