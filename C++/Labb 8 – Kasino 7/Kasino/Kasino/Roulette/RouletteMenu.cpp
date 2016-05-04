#include "stdafx.h"
#include "RouletteMenu.h"

namespace Kasino {
namespace Roullete {
bool RouletteMenu(float &abetAmount, float &aBettingOdds, bool &aUserWin, float & aUserMoney)
{
	std::string tMenuOptions = "How would you like to bet? \n 1 - Single \n 2 - Split \n 3 - Street \n 4 - Corner \n 5 - Double Street \n 6 - 1-18-Manque \n 7 - 19-36-Passe \n 8 - Red or Black \n 9 - Even or Odd \n 10 - Dozen bet, \n 11 - Collumn bet \n \n 12 - Leave Roulette Table";
	int playerBettingChoice = MyFunctions::Console::AskForNumber(tMenuOptions, 1, static_cast<int>(Kasino::Roullete::General::enumRouletteBetTypes::enumLenght));
	switch (static_cast<Kasino::Roullete::General::enumRouletteBetTypes>(playerBettingChoice))
	{
	case Kasino::Roullete::General::enumRouletteBetTypes::eSingle:
	{
		Kasino::Roullete::RoulettePlaySingle(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::eSplit:
	{
		Kasino::Roullete::RoulettePlaySplit(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::eStreet:
	{
		Kasino::Roullete::RoulettePlayStreet(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::eCorner:
	{
		Kasino::Roullete::RoulettePlayCorner(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::eDoubleStreet:
	{
		Kasino::Roullete::RoulettePlayDoubleStreet(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::eManque:
	{
		Kasino::Roullete::RoulettePlayManque(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::ePasse:
	{
		Kasino::Roullete::RoulettePlayPasse(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::eRedOrBlack:
	{
		Kasino::Roullete::RoulettePlayRedOrBlack(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::EvenorOdd:
	{
		Kasino::Roullete::RoulettePlayEvenOrOdd(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::DozenBet:
	{
		Kasino::Roullete::RoulettePlayDozen(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::Column:
	{
		Kasino::Roullete::RoulettePlayColumn(abetAmount, aBettingOdds, aUserWin, aUserMoney);
		break;
	}
	case Kasino::Roullete::General::enumRouletteBetTypes::enumLenght:
	{
		std::cout << "Player Leaves Table" << std::endl;
		return false;
		break;
	}
	default:
	{
		std::cout << "ERROR Betting out of ID range" << std::endl;
		break;
	}
	}
	return true;
}
}
}
