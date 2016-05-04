#include "stdafx.h"
#include "NormalRoulette.h"


NormalRoulette::NormalRoulette()
{
}


NormalRoulette::~NormalRoulette()
{
}

void NormalRoulette::PlayGame(Player & aThePlayer)
{
	bool playAgain = Kasino::General::GiveInstructions("Welcome to roulette table", "straight(or Single)a single number bet.The chip is placed entirely on the middle of a number square. Split a bet on two adjoining numbers, either on the vertical or horizontal(as in 14 - 17 or 8 - 9).The chip is placed on the line between these numbers. Street a bet on three numbers on a single horizontal line.The chip is placed on the edge of the line of a number at the end of the line(either the left or the right, depending on the layout). Corner(or Square) a bet on four numbers in a square layout(as in 11 - 12 - 14 - 15).The chip is placed at the horizontal and vertical intersection of the lines between the four numbers. Six line(or Double Street) a bet on two adjoining streets, with the chip placed at the corresponding intersection, as if in between where two street bets would be placed. Trio a bet on the intersecting point between 0, 1 and 2, or 0, 2 and 3 (single - zero layout only). Basket(or the first four) (non - square corner) a bet on 0, 1, 2, and 3 (single - zero layout only). Basket a bet on 0, 1, and 2; 0, 00, and 2; or 00, 2, and 3 (double - zero layout only).The chip is placed at the intersection of the three desired numbers. Top line a bet on 0, 00, 1, 2, and 3 (double - zero layout only).The chip is placed either at the corner of 0 and 1, or the corner of 00 and 3. 1 to 18 (Manque) a bet on one of the first low eighteen numbers coming up. 19 to 36 (Passe) a bet on one of the latter high eighteen numbers coming up. Red or black(Rouge ou Noir) a bet on which color the roulette wheel will show. Even or odd(Pair ou Impair) a bet on an even or odd nonzero number. Dozen bets a bet on the first(1 - 12, Premiere douzaine(P12)), second(13 - 24, Moyenne douzaine(M12)), or third group(25 - 36, Dernière douzaine(D12)) of twelve numbers. Column bets a bet on all 12 numbers on any of the three vertical lines(such as 1 - 4 - 7 - 10 on down to 34).The chip is placed on the space below the final number in this sequence.", myCashFlow.GetTableFeelingsState());

	std::cout << std::endl;
	std::cout << std::endl;



	while (playAgain)
	{
		float userBetAmount;
		float odds;
		bool userWin;
		//std::cout << "ROULETTE IS A SHITTY GAME WHY WOULD YOU WANT TO PLAY IT?" << std::endl;
		//system("pause");
		float tmpMoney = aThePlayer.GetMoney();
		if (Kasino::Roullete::RouletteMenu(userBetAmount, odds, userWin, tmpMoney))
		{
			Kasino::General::PrintWinOrLose(userBetAmount, odds, userWin, aThePlayer, myCashFlow);

			playAgain = Kasino::General::PlayAgainCheck(aThePlayer, myCashFlow);
		}
		else
		{
			playAgain = false;
		}

	}
}