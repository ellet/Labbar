#pragma once
#include "KasinoGeneralFunctions.h"
#include "CashFlow.h"
class GuessEvenOrUneven
{
public:
	GuessEvenOrUneven();
	~GuessEvenOrUneven();

	void PlayGame(Player & aThePlayer);

private:
	CashFlow myCashFlow;
};