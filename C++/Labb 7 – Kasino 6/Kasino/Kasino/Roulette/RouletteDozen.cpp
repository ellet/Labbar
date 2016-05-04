#include "stdafx.h"
#include "RouletteDozen.h"

namespace Kasino {
namespace Roullete {
void RoulettePlayDozen(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(12);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = MyFunctions::Console::AskForNumber("Which set of dozen would you like to bet on? 1 - 1-12, 2 - 13-24, 3 - 25-36", 1, 3) - 1;

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

	const Kasino::Roullete::General::enumDozenTypes BallDozenType = Kasino::Roullete::General::GetDozenTypeFromSquare(BallLandedOn);
	const Kasino::Roullete::General::enumDozenTypes PlayerDozenType = static_cast<Kasino::Roullete::General::enumDozenTypes>(PlayerBetOn);

	std::cout << "You bet on : " << Kasino::Roullete::General::GetStringRouletteDozenType(PlayerDozenType) << std::endl;
	std::cout << "Results are: " << Kasino::Roullete::General::GetStringRouletteDozenType(BallDozenType) << std::endl;

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
}
}
