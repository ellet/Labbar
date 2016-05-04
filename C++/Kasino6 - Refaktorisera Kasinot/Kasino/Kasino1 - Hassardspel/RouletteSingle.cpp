#include "stdafx.h"
#include "RouletteSingle.h"

namespace Kasino {
namespace Roullete {
void RoulettePlaySingle(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(1);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = MyFunctions::Console::AskForNumber("Which number would you like to bet on? Bet on a number between 0 to 36", 0, 36);

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

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
}
}
