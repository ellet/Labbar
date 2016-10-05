#include "stdafx.h"
#include "BouncingComponent.h"
#include "Engine/GameObject/GameObject.h"
#include <Utilities/Math/MathMacros.h>

namespace ENGINE_NAMESPACE
{
	BouncingComponent::BouncingComponent()
	{
		const float velocityMagic = 3.f;
		myVelocity = Vector3f(velocityMagic, velocityMagic, velocityMagic);
		myMovingTowardsPoint = Vector3f(0.f, 20.f, 0.f);
		myThrowingAwayVelocity = Vector3f(0.f, 0.f, 0.f);
		myPointGravity = 0.0098f;
	}

	BouncingComponent::~BouncingComponent()
	{
	}

	void BouncingComponent::Update(const Time & aDeltaTime)
	{
		MoveObject(aDeltaTime);
	}

	void BouncingComponent::Render() const
	{
		Engine::GetDebugger().DrawLine(myMovingTowardsPoint, myObject->GetPosition(), Vector4f(0.f, 0.f, 0.f, 1.f));
		Engine::GetDebugger().DrawLine(myObject->GetPosition() + myRotAxis.GetNormalized() * 5.f, myObject->GetPosition(), Vector4f(0.f, 0.f, 1.f, 1.f));
		Engine::GetDebugger().DrawLine(myObject->GetPosition() + myObject->GetRotation().GetForward(), myObject->GetPosition(), Vector4f(1.f, 0.f, 0.f, 1.f));
		Engine::GetDebugger().DrawLine(myObject->GetPosition() + myObject->GetRotation().GetForward(), myMovingTowardsPoint, Vector4f(0.f, 1.f, 0.f, 1.f));
	}

	void BouncingComponent::Initialize()
	{

	}

	void BouncingComponent::MoveObject(const Time & aDeltaTime)
	{
		Vector3f currentDirection = myObject->GetRotation().GetForward();
		Vector3f newPosition = myObject->GetPosition() + (currentDirection * aDeltaTime.InSeconds() * 5.f); 
		myObject->SetPosition(newPosition);

		Vector3f targetDirection = myMovingTowardsPoint - myObject->GetPosition(); 
		RotateObject(aDeltaTime, targetDirection, currentDirection);
		
		if (targetDirection.Length() <= 1.f)
		{
			myMovingTowardsPoint.x = myRandomizer.GetRandomValue(-10, 10);
			myMovingTowardsPoint.y = myRandomizer.GetRandomValue(-10, 10);
			myMovingTowardsPoint.z = myRandomizer.GetRandomValue(-10, 10);
		}
		else if (targetDirection.Length() > 100.f)
		{
			int missedIt = 0;
			++missedIt;
		}
	}

	void BouncingComponent::RotateObject(const Time & aDeltaTime, const Vector3f & aTargetDirection, const Vector3f & aCurrentDirection)
	{
		const float DirectionEpsilon = 0.05f;

		if (aTargetDirection.GetNormalized().x + DirectionEpsilon >= aCurrentDirection.GetNormalized().x - DirectionEpsilon &&
			aTargetDirection.GetNormalized().x - DirectionEpsilon <= aCurrentDirection.GetNormalized().x + DirectionEpsilon &&
			aTargetDirection.GetNormalized().y + DirectionEpsilon >= aCurrentDirection.GetNormalized().y - DirectionEpsilon &&
			aTargetDirection.GetNormalized().y - DirectionEpsilon <= aCurrentDirection.GetNormalized().y + DirectionEpsilon &&
			aTargetDirection.GetNormalized().z + DirectionEpsilon >= aCurrentDirection.GetNormalized().z - DirectionEpsilon &&
			aTargetDirection.GetNormalized().z - DirectionEpsilon <= aCurrentDirection.GetNormalized().z + DirectionEpsilon)
		{
			return; //On course
		}

		Vector3f rotAxis = Vector3f::Cross(aTargetDirection, aCurrentDirection);
		//Vector3f perpendicular = Vector3f::Cross(rotAxis, aCurrentDirection); Might be an idea to deduce the perpendicular line to current & axis, to dot targetDir on perpendicular
		rotAxis.Normalize();

		// if this is true, then we are on course, or the opposite course :[
		if (isnan(rotAxis.z) == true || isnan(rotAxis.y) == true || isnan(rotAxis.x) == true)
		{
			return;
		}

		myRotAxis = rotAxis;

		float angle = GetAngle(aTargetDirection.Length(), aCurrentDirection.Length(), (aTargetDirection - aCurrentDirection).Length());

		if (isnan(angle) == true)
		{
			return;
		}

		Quaternion toRotateForSign = myObject->GetRotation();
		toRotateForSign.RotateAlongAxis(rotAxis, angle);
		float testSign = (aTargetDirection - (toRotateForSign * aCurrentDirection)).Length();

		if (testSign > (aTargetDirection - aCurrentDirection).Length()) //Are we maybe rotating to the right instead?
		{
			angle = -angle; //Then flip angle
		}

		const float MaxRotation = DEGRESS_TO_RADIANSF(5.f);

		if (angle > MaxRotation)
		{
			angle = MaxRotation;
		}
		else if (angle < -MaxRotation)
		{
			angle = -MaxRotation;
		}

		myObject->RotateAlongAxis(rotAxis, angle);
	}

	float BouncingComponent::GetAngle(const float aFirstSide, const float aSecondSide, const float aThirdSide) const
	{
		float firstSide = aFirstSide;
		float secondSide = aSecondSide;
		float thirdSide = aThirdSide;

		if (thirdSide < firstSide) //If hypotenuse isn't the third side, swap the values to a "real" hypotenuse, to make sure the third side IS the longest
		{
			firstSide = thirdSide;
			thirdSide = firstSide;
		}
		else if (thirdSide < secondSide) //and again
		{
			secondSide = thirdSide;
			thirdSide = secondSide;
		}

		return acos(((-firstSide*firstSide - secondSide*secondSide + thirdSide*thirdSide) / (-2 * firstSide * secondSide)));
	}

}
