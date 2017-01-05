#include "stdafx.h"
#include "SeekBehaviour.h"
#include "..\TheLabs\Unit.h"

const float TargetRadius = 5.f;

float SeekBehaviour::ourWeight;

SeekBehaviour::SeekBehaviour(const Unit & aParentUnit) : BaseBehaviour(aParentUnit)
{
	myShouldMoveToTarget = false;
	myTargetPosition = SB::Vector2f::Zero;
}


SeekBehaviour::~SeekBehaviour()
{
}

Steering SeekBehaviour::GetSteering(const SB::Time & aDeltaTime)
{
	myWeight = ourWeight;

	Steering mySteering;
	mySteering.Direction = SB::Vector2f::Zero;


	if (myShouldMoveToTarget == true)
	{
		const SB::Vector2f DirectionVector = myTargetPosition - myParentUnit->GetPosition();
		const float LengthDifference = DirectionVector.Length();

		if (LengthDifference > TargetRadius)
		{
			mySteering.Direction = DirectionVector.GetNormalized() * myWeight;
			mySteering.SpeedPercentage = 1.f;
			return mySteering;
		}

		myShouldMoveToTarget = false;
	}

	return mySteering;
}


