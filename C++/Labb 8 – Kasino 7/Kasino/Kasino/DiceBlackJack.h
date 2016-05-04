#pragma once
#include "KasinoGeneralFunctions.h"
#include "CashFlow.h"

class DiceBlackJack
{
public:
	DiceBlackJack();
	~DiceBlackJack();
	
	void PlayGame(Player & aThePlayer);

private:
	CashFlow myCashFlow;
};