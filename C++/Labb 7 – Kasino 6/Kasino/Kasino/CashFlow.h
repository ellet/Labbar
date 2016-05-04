#pragma once
#include "CashFlowEnum.h"
//#include "KasinoGeneralFunctions.h"

class CashFlow
{

public:
	CashFlow();
	~CashFlow();

	void SetThresholds(float aLikeValue, float aNeutralValue, float aDislikeValuem, float aHateValue);
	void ChangeCurrentFlow(float aChangeWith);

	enumTableLikeStates GetTableFeelingsState() const;
	float GetTableWinningsValue() const;

private:
	void CheckAndChangeLikeState();

	enumTableLikeStates myTableFeelingsState;

	float myCurrentValueStanding;
	float myNeutralStanding;
	float myGoodStanding;
	float myBadStanding;
	float myKickOutStanding;
};

