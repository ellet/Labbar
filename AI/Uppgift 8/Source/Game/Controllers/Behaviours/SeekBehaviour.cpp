#include "stdafx.h"
#include "SeekBehaviour.h"
#include "Utilities\Math\Vector2.h"

const float MinDistance = 5.f;

SeekBehaviour::SeekBehaviour(const BaseController & aController) : BaseBehaviour(aController)
{
	myTargetPosition = GetPosition();
}


SeekBehaviour::~SeekBehaviour()
{
}


Steering SeekBehaviour::UpdateSteering(const float /*aDeltaTime*/)
{
	Steering output;

	const SB::Vector2f DirectionVector = myTargetPosition - GetPosition();

	if (DirectionVector.Length() > MinDistance)
	{
		output.Direction = DirectionVector.GetNormalized();
		output.SpeedPercentage = 1.f;
	}

	return output;
}

void SeekBehaviour::SetTargetPosition(const SB::Vector2f & aTargetPosition)
{
	myTargetPosition = aTargetPosition;
}

