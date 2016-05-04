#include "stdafx.h"
#include "LiftAndReleaseWeight.h"
#include "../../Object/OnOffWeigth.h"

LiftAndReleaseWeight::LiftAndReleaseWeight(OnOffWeigth * aOnOffWeight)
{
	myOnOffWeight = aOnOffWeight;
}


LiftAndReleaseWeight::~LiftAndReleaseWeight()
{
}

void LiftAndReleaseWeight::OneShotEvent()
{
	if (myOnOffWeight->GetLiftedState() == true)
	{
		myOnOffWeight->SetDropped();
	}
	else
	{
		myOnOffWeight->SetLifted();
	}
}
