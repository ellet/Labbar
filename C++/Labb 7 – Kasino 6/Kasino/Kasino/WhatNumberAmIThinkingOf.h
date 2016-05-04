#pragma once
#include "KasinoGeneralFunctions.h"
#include "CashFlow.h"
class WhatNumberAmIThinkingOf
{
public:
	WhatNumberAmIThinkingOf();
	~WhatNumberAmIThinkingOf();
	void PlayGame(Player & aThePlayer);

private:
	CashFlow myCashFlow;
};