#pragma once
#include "Player.h"
#include "KasinoGeneralFunctions.h"
#include "GuessNumber.h"
#include "DiceBlackJack.h"
#include "GuessEvenOrUneven.h"
#include "RockPaperScissors.h"
#include "GuessMoreOrLess.h"
#include "WhatNumberAmIThinkingOf.h"
#include "RussianRoulette.h"
#include "NormalRoulette.h"


class KasinoClass
{
public:
	KasinoClass();
	~KasinoClass();

	void RunKasino();

private:
	Player myPlayer;
	GuessNumber myGuessNumberGame;
	DiceBlackJack myDiceBlackJack;
	GuessEvenOrUneven myGuessEvenOrUneven;
	RockPaperScissors myRockPaperScissors;
	GuessMoreOrLess myGuessMoreOrLess;
	WhatNumberAmIThinkingOf myWhatNumberAmIThinkingOf;
	RussianRoulette myRussianRoulette;
	NormalRoulette myNormalRoulette;
};