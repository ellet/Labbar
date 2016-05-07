#include "stdafx.h"
#include "RouletteManque.h"

namespace Kasino {
namespace Roullete {
void RoulettePlayManque(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(18);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

	std::cout << "You bet between 1 and 18: " << std::endl;
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
}
}