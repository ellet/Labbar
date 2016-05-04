#include "stdafx.h"
#include "RouletteRedOrBlack.h"

namespace Kasino {
namespace Roullete {
void RoulettePlayRedOrBlack(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(18);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = MyFunctions::Console::AskForNumber("Which color would you like to bet on? 1 - Black, 2 - Red", 1, 2) - 1;

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

	const Kasino::Roullete::General::enumRouletteColor BallColor = Kasino::Roullete::General::GetColorFromSquare(BallLandedOn);
	const Kasino::Roullete::General::enumRouletteColor PlayerColor = static_cast<Kasino::Roullete::General::enumRouletteColor>(PlayerBetOn);

	std::cout << "You bet on : " << Kasino::Roullete::General::GetStringRouletteColorFromEnum(PlayerColor) << std::endl;
	std::cout << "Results are: " << Kasino::Roullete::General::GetStringRouletteColorFromEnum(BallColor) << std::endl;

	if (BallLandedOn != 0)
	{
		if (PlayerColor == BallColor)
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
