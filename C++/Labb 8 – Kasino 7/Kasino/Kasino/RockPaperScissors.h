#pragma once
#include "KasinoGeneralFunctions.h"
#include "CashFlow.h"
class RockPaperScissors
{
public:
	RockPaperScissors();
	~RockPaperScissors();

	void PlayGame(Player & aThePlayer);

private:
	std::string TranslateNumberToRockPaperScissors(const int aChoosenType);

	CashFlow myCashFlow;
};