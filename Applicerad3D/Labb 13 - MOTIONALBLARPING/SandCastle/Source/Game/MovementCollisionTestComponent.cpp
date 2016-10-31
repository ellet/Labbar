#include "stdafx.h"
#include "MovementCollisionTestComponent.h"


MovementCollisionTestComponent::MovementCollisionTestComponent()
{
}


MovementCollisionTestComponent::~MovementCollisionTestComponent()
{
}

void MovementCollisionTestComponent::SetVelocity(const SB::Vector3f & aVelocity)
{
	myVelocity = aVelocity;
}

void MovementCollisionTestComponent::Update(const SB::Time & aDeltaTime)
{
	SB::Vector3f tempPosition = GetMovement(aDeltaTime);

	if (CheckIfInside(tempPosition) == true)
	{
		myObject->SetPosition(tempPosition);
	}
	else
	{
		myVelocity = -myVelocity;
		myObject->SetPosition(GetMovement(aDeltaTime));
	}
}

void MovementCollisionTestComponent::Render() const
{

}

SB::Vector3f MovementCollisionTestComponent::ourConstraints;

SB::Vector3f MovementCollisionTestComponent::GetMovement(const SB::Time & aDeltaTime)
{
	SB::Vector3f tempPosition = myObject->GetPosition();

	tempPosition += myVelocity * aDeltaTime.InSeconds();

	return tempPosition;
}

bool MovementCollisionTestComponent::CheckIfInside(const SB::Vector3f & aPosition)
{
	if ((aPosition.x < ourConstraints.x && aPosition.x > -ourConstraints.x) &&
		(aPosition.y < ourConstraints.y && aPosition.y > -ourConstraints.y) &&
		(aPosition.z < ourConstraints.z && aPosition.z > -ourConstraints.z))
	{
		return true;
	}

	return false;
}
