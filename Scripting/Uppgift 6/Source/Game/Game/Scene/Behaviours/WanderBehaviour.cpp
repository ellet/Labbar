#include "stdafx.h"
#include "WanderBehaviour.h"
#include "..\TheLabs\Unit.h"


const float MaxRotationAmount = 45.f;

float WanderBehaviour::ourWeight;

WanderBehaviour::WanderBehaviour(const Unit & aParentUnit) : BaseBehaviour(aParentUnit)
{
}

WanderBehaviour::~WanderBehaviour()
{
}

Steering WanderBehaviour::GetSteering(const SB::Time & aDeltaTime)
{
	myWeight = ourWeight;
	
	Steering output;
	output.SpeedPercentage = 0.75f;


	SB::Vector2f currentOriantation = myParentUnit->GetDirection();

	currentOriantation = currentOriantation * SB::Matrix33f::CreateRotateAroundZ(GetRandomBinomial() * (MaxRotationAmount * aDeltaTime.InSeconds()));

	output.Direction = currentOriantation * myWeight;

	return output;
}



float WanderBehaviour::GetRandomBinomial()
{
	return (myRandomizer.GetRandomValue(0.f, 1.f) - myRandomizer.GetRandomValue(0.f, 1.f));
}
