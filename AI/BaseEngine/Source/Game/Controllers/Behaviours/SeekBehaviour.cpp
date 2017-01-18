#include "stdafx.h"
#include "SeekBehaviour.h"


SeekBehaviour::SeekBehaviour(const BaseController & aController) : BaseBehaviour(aController)
{
	myTargetPosition = GetPosition();
}


SeekBehaviour::~SeekBehaviour()
{
}


Steering SeekBehaviour::UpdateSteering(const float aDeltaTime)
{
	Steering output;

	const SB::Vector2f DirectionVector = myTargetPosition - GetPosition();

	output.Direction = DirectionVector.GetNormalized();
	output.SpeedPercentage = 1.f;

	return output;
}

void SeekBehaviour::SetTargetPosition(const SB::Vector2f & aTargetPosition)
{
	myTargetPosition = aTargetPosition;
}

