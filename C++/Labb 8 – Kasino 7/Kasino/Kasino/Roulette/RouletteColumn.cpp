#include "stdafx.h"
#include "RouletteColumn.h"

namespace Kasino {
namespace Roullete {
void RoulettePlayColumn(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	aBettingOdds = Kasino::Roullete::General::GetRouletteOddsFormula(12);
	abetAmount = Kasino::General::BetMoney(aBettingOdds, aUserMoney);
	aUserWin = false;
	std::cout << std::endl;
	std::cout << std::endl;

	const int PlayerBetOn = MyFunctions::Console::AskForNumber("Which column would you like bet on? 1 to 3", 1, 3) - 1;

	const int BallLandedOn = Kasino::Roullete::General::RollRoulleteBall();

	const Kasino::Roullete::General::enumRouletteColumn BallColumn = Kasino::Roullete::General::CheckForRouletteColumn(BallLandedOn);
	const Kasino::Roullete::General::enumRouletteColumn PlayerColumn = static_cast<Kasino::Roullete::General::enumRouletteColumn>(PlayerBetOn);

	std::cout << "You bet on column : " << Kasino::Roullete::General::GetStringRouletteColumnFromEnum(PlayerColumn) << std::endl;
	std::cout << "Winning row is: " << Kasino::Roullete::General::GetStringRouletteColumnFromEnum(BallColumn) << std::endl;

	if (BallLandedOn != 0)
	{
		if (BallColumn == PlayerColumn)
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
