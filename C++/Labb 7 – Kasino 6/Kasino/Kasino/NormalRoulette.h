#pragma once
#include "KasinoGeneralFunctions.h"
#include "CashFlow.h"
#include "Roulette\RouletteGeneralFunctions.h"
#include "Roulette\RouletteMenu.h"
class NormalRoulette
{
public:
	NormalRoulette();
	~NormalRoulette();

	void PlayGame(Player & aThePlayer);

private:
	CashFlow myCashFlow;
};