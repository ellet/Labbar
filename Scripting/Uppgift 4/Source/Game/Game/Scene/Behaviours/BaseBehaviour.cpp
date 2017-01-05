#include "stdafx.h"
#include "BaseBehaviour.h"


BaseBehaviour::BaseBehaviour(const Unit& aParentUnit) : myParentUnit(&aParentUnit)
{
	myWeight = 0.f;
}


BaseBehaviour::~BaseBehaviour()
{
}

void BaseBehaviour::SetWeight(const float aWeight)
{
	myWeight = aWeight;
}
