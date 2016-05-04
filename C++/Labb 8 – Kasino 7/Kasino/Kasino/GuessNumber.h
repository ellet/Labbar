#pragma once
#include "CashFlow.h"
#include "KasinoGeneralFunctions.h"

class GuessNumber
{
public:
	GuessNumber();
	~GuessNumber();

	void PlayGame(Player & aThePlayer);

private:
	CashFlow myCashFlow;
};