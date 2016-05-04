#pragma once
#include "KasinoGeneralFunctions.h"
#include "CashFlow.h"
class RussianRoulette
{
public:
	RussianRoulette();
	~RussianRoulette();
	
	void PlayGame(Player & aThePlayer);

private:
	CashFlow myCashFlow;

	bool myIsDealerAlive;
};