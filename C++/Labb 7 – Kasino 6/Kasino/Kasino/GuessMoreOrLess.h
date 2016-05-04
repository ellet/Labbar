#pragma once
#include "KasinoGeneralFunctions.h"
#include "CashFlow.h"
class GuessMoreOrLess
{
	enum class enumLessAndMore
	{
		eLess = 1,
		eMore = 2
	};

public:
	GuessMoreOrLess();
	~GuessMoreOrLess();

	void PlayGame(Player & aThePlayer);

private:
	CashFlow myCashFlow;
};