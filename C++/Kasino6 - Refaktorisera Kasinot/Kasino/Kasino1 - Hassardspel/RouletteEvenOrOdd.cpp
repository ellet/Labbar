#include "stdafx.h"
#include "RouletteEvenOrOdd.h"

namespace Kasino {
namespace Roullete {
void RoulettePlayEvenOrOdd(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(18);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = MyFunctions::Console::AskForNumber("Which color would you like to bet on? 1 - Odd, 2 - Even", 1, 2);

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

	std::cout << "You bet on : " << Kasino::Roullete::General::GetStringRouletteOddOrEven(PlayerBetOn) << std::endl;
	std::cout << "Results are: " << Kasino::Roullete::General::GetStringRouletteOddOrEven(BallLandedOn) << std::endl;

	if (BallLandedOn != 0)
	{
		if (MyFunctions::Math::CheckNumberIfEven(PlayerBetOn) == MyFunctions::Math::CheckNumberIfEven(BallLandedOn))
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
