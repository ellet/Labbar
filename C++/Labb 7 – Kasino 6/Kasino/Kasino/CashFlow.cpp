#include "stdafx.h"
#include "CashFlow.h"


CashFlow::CashFlow()
{
	myTableFeelingsState = enumTableLikeStates::eNeutral;

	myCurrentValueStanding = 0;
	myNeutralStanding = 0;
	myGoodStanding = 0;
	myBadStanding = 0;
	myKickOutStanding = 0;
}


CashFlow::~CashFlow()
{
}

void CashFlow::ChangeCurrentFlow(float aChangeWith)
{
	myCurrentValueStanding += aChangeWith;

	CheckAndChangeLikeState();
}

void CashFlow::SetThresholds(float aLikeValue, float aNeutralValue, float aDislikeValue, float aHateValue)
{
	myNeutralStanding = aNeutralValue;
	myGoodStanding = aLikeValue;
	myBadStanding = aDislikeValue;
	myKickOutStanding = aHateValue;

	CheckAndChangeLikeState();
}

enumTableLikeStates CashFlow::GetTableFeelingsState() const
{
	return myTableFeelingsState;
}

float CashFlow::GetTableWinningsValue() const
{
	return myCurrentValueStanding;
}

void CashFlow::CheckAndChangeLikeState()
{
	if (myCurrentValueStanding <= myGoodStanding)
	{
		myTableFeelingsState = enumTableLikeStates::eLike;
		return;
	}
	else if (myCurrentValueStanding < myBadStanding)
	{
		myTableFeelingsState = enumTableLikeStates::eNeutral;
		return;
	}
	else if (myCurrentValueStanding < myKickOutStanding)
	{
		myTableFeelingsState = enumTableLikeStates::eDislike;
		return;
	}
	else
	{
		myTableFeelingsState = enumTableLikeStates::eHate;
		return;
	}
}