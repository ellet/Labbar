#include "stdafx.h"
#include "CircleMovementComponent.h"
#include <Utilities/Math/MathMacros.h>

namespace SB
{

	CircleMovementComponent::CircleMovementComponent()
	{
		myProgress = 0.f;
	}


	CircleMovementComponent::~CircleMovementComponent()
	{
	}

	void CircleMovementComponent::Update(const Time& aDeltaTime)
	{
		myProgress += aDeltaTime;
		//myObject->RotateAlongAxis(Vector3f(0.f, 1.f, 0.f), DEGREES_TO_RADIANSF(5.f * aDeltaTime.InSeconds()));

		Vector3f oldPosition = myObject->GetPosition();
		myObject->SetPosition(myOrigin + Vector3f(sin(myProgress.InSeconds()), 0.f, cos(myProgress.InSeconds())) * 3.f);
		myObject->SetRotation(Quaternion::CreateFromVectors(oldPosition, myObject->GetPosition(), Vector3f(0.f, 1.f, 0.f)));
	}

	void CircleMovementComponent::Initialize()
	{
		myOrigin = myObject->GetTransformation().GetPosition();
	}
}
