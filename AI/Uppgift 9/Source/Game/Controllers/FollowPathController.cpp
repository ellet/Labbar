#include "stdafx.h"
#include "FollowPathController.h"
#include "..\Actors\Actor.h"


const float MinDistance = 4.f;
const float MovementSpeed = 175.f;

FollowPathController::FollowPathController(const Actor & aActor) : BaseController(aActor), mySeekBehaviour(*this)
{
}


FollowPathController::~FollowPathController()
{
}

SB::Vector2f FollowPathController::Update(const float aDeltaTime)
{
	if (myPath.Size() > 0)
	{
		const float CurrentDistance = (mySeekBehaviour.GetTargetPosition() - GetActor().GetPosition()).Length();

		if (CurrentDistance <= MinDistance)
		{
			SetTargetPosition(myPath[0]);
			myPath.RemoveAtIndex(0);
		}
	}

	Steering output;
	output += mySeekBehaviour.UpdateSteering(aDeltaTime);

	return output.Direction * MovementSpeed * output.SpeedPercentage * aDeltaTime;
}

void FollowPathController::SetPath(const SB::GrowingArray<SB::Vector2f> aPath)
{
	myPath = aPath;
}

void FollowPathController::SetTargetPosition(const SB::Vector2f & aTargetPosition)
{
	mySeekBehaviour.SetTargetPosition(aTargetPosition);
}
