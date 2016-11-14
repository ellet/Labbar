#include "stdafx.h"
#include "BouncingComponent.h"
#include "Engine/GameObject/GameObject.h"
#include <Utilities/Math/MathMacros.h>
#include <imgui.h>
#include <Engine/Scene/Scene.h>
#include <Engine/Camera/Camera.h>

namespace ENGINE_NAMESPACE
{
	BouncingComponent::BouncingComponent()
	{

		myActivatePoint = 0;
		myPointPaths.Add(Vector3f(-10.f, -10.f, 10.f));
		myPointPaths.Add(Vector3f(-10.f, -10.f, -10.f));
		myPointPaths.Add(Vector3f(10.f, -10.f, -10.f));
		myPointPaths.Add(Vector3f(10.f, -10.f, 10.f));

		myAngleIsPositive = true;
		myShouldProgress = false;

		//For Lerp and move with keys tests ---------
		//
		//myRotProgress = 0.f;
		//myHasRot = false;
		//myHasFirst = false;
		//
		//myPitchForward = false;
		//myPitchBackward = false;
		//myRollLeft = false;
		//myRollRight = false;
		//myRotateLeft = false;
		//myRotateRight = false;
		//myMoveLeft = false;
		//myMoveRight = false;
		//myMoveUp = false;
		//myMoveDown = false;
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
		//DebugDraw();
	}

	void BouncingComponent::Initialize()
	{

	}

	void BouncingComponent::MoveObject(const Time & aDeltaTime)
	{
		//Target position is right now camera, but try with hard coded points initialized in constructor instead
		const Vector3f TargetPosition = myPointPaths[myActivatePoint];


		const float MaxRotationInDegrees = 10.f;
		RotateTowardsPoint(aDeltaTime, TargetPosition, MaxRotationInDegrees);
		Vector3f newPosition = myObject->GetPosition() + (myObject->GetRotation().GetForward() * aDeltaTime.InSeconds() * 5.f);
		myObject->SetPosition(newPosition);

		if ((TargetPosition - myObject->GetPosition()).Length() <= 1.f)
		{
			myShouldProgress = true;
		}
		
		if (myShouldProgress == true)
		{
			myShouldProgress = false;
			myActivatePoint++;
			if (myActivatePoint >= myPointPaths.Size())
			{
				myActivatePoint = 0;
			}
		}
	}

	void BouncingComponent::RotateTowardsPoint(const Time & aDeltaTime, const Vector3f & aTargetPosition, const float aMaxRotationInDegrees)
	{

		const Vector3f CurrentDirection = myObject->GetRotation().GetForward().GetNormalized();
		const float sign = myObject->GetRotation().GetRight().GetNormalized().Dot(aTargetPosition - myObject->GetPosition()); //Sign is positive to the right, negative to the left
		Vector3f rotAxis;

		if (sign > M_EPSILONF) // right
		{
			rotAxis = Vector3f::Cross(CurrentDirection, aTargetPosition - myObject->GetPosition());
			myAngleIsPositive = true;
		}
		else if (sign < M_EPSILONF) //left
		{
			rotAxis = Vector3f::Cross(aTargetPosition - myObject->GetPosition(), CurrentDirection);
			myAngleIsPositive = false;
		}
		else //on track or point is precisely behind us
		{
			return;
		}
		
		// if this is true, then we are on the opposite course :[ (or right course, but we handled that before we called the function)
		if (isnan(rotAxis.z) == true || isnan(rotAxis.y) == true || isnan(rotAxis.x) == true || rotAxis == Vector3f::Zero)
		{
			return;
		}

		myRotAxis = rotAxis;//For debug draw purposes

		float angle = GetAngleWithCross(rotAxis);

		if (isnan(angle) == true || angle == 0.f)
		{
			return;
		}

		const float MaxRotation = DEGREES_TO_RADIANSF(aMaxRotationInDegrees);

		if (angle > MaxRotation)
		{
			angle = MaxRotation;
		}

		angle *= aDeltaTime.InSeconds();


		if (myAngleIsPositive == false)
		{
			angle *= -1.f;
		}

		myObject->RotateAlongAxis(myRotAxis, angle);
	}

	float BouncingComponent::GetAngleWithCross(const Vector3f & aProductFromNormalizedVectors) const
	{
		//Look in linalg book for proof that this works. Page 67. Only works for cross product of two NORMALIZED vectors

		float crossLength = aProductFromNormalizedVectors.Length();

		//Clamp for float problems
		if (crossLength > 1.f)
		{
			crossLength = 1.f;
		}
		else if (crossLength < 0.f)
		{
			crossLength = 0.f;
		}

		return asin(crossLength);
	}

	//--------------------------------

	//void BouncingComponent::RotateWithLerp(const Time & aDeltaTime, const Vector3f & aTargetDirection)
	//{
	//	if (myHasRot == false)
	//	{
	//		myTargetRot = Quaternion::CreateFromVectors(myObject->GetPosition(), aTargetDirection.GetNormalized(), myObject->GetRotation().GetUpward()); //Saving it for debug drawing
	//		myHasRot = true;
	//	}
	//	myObject->SetRotation(Quaternion::Lerp(myObject->GetRotation(), myTargetRot, myRotProgress));
	//}

	//void BouncingComponent::RotateTestLookAtCamera()
	//{
	//	myTargetRot = Quaternion::CreateFromVectors(myObject->GetPosition(), myObject->GetScene().GetCamera().GetPosition(), myObject->GetRotation().GetUpward()); //Saving it for debug drawing
	//	myObject->SetRotation(myTargetRot);
	//}

	//-----------------------------------

	void BouncingComponent::DebugDraw()
	{
		
		SB::Engine::GetDebugDrawer().DrawLine(myPointPaths[myActivatePoint], myPointPaths[myActivatePoint] + myTargetRot.GetRight().GetNormalized() * 5.f , Vector4f(1.f, 0.f, 0.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myPointPaths[myActivatePoint], myPointPaths[myActivatePoint] + myTargetRot.GetUpward().GetNormalized() * 5.f, Vector4f(0.f, 1.f, 0.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myPointPaths[myActivatePoint], myPointPaths[myActivatePoint] + myTargetRot.GetForward().GetNormalized() * 5.f, Vector4f(0.f, 0.f, 1.f, 1.f));
		
		SB::Engine::GetDebugDrawer().DrawLine(myPointPaths[0], myPointPaths[1], Vector4f(1.f, 0.f, 1.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myPointPaths[2], myPointPaths[1], Vector4f(1.f, 0.f, 1.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myPointPaths[2], myPointPaths[3], Vector4f(1.f, 0.f, 1.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myPointPaths[0], myPointPaths[3], Vector4f(1.f, 0.f, 1.f, 1.f));
		
		SB::Engine::GetDebugDrawer().DrawLine(myObject->GetPosition() + myObject->GetRotation().GetForward() * 5.f, myObject->GetPosition(), Vector4f(0.f, 0.f, 1.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myObject->GetPosition() + myObject->GetRotation().GetRight() * 5.f, myObject->GetPosition(), Vector4f(1.f, 0.f, 0.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myObject->GetPosition() + myObject->GetRotation().GetUpward() * 5.f, myObject->GetPosition(), Vector4f(0.f, 1.f, 0.f, 1.f));
		
		SB::Engine::GetDebugDrawer().DrawLine(myPointPaths[myActivatePoint], myObject->GetPosition(), Vector4f(0.f, 0.f, 0.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myObject->GetPosition() + myRotAxis.GetNormalized() * 5.f, myObject->GetPosition(), Vector4f(1.f, 0.f, 1.f, 1.f));
		SB::Engine::GetDebugDrawer().DrawLine(myObject->GetPosition() + myObject->GetRotation().GetForward(), myPointPaths[myActivatePoint], Vector4f(0.f, 1.f, 0.f, 1.f));
		
	}

	//---------------------------------------------------


	ENGINE_NAMESPACE::ReceiveResult BouncingComponent::Receive(const AnyKeyUpMessage & aMessage)
	{
		//switch (aMessage.key)
		//{
		//case KeyboardKey::eU:
		//	myRollLeft = false;
		//	break;
		//case KeyboardKey::eO:
		//	myRollRight = false;
		//	break;
		//case KeyboardKey::eJ:
		//	myRotateLeft = false;
		//	break;
		//case KeyboardKey::eL:
		//	myRotateRight = false;
		//	break;
		//case KeyboardKey::eI:
		//	myPitchForward = false;
		//	break;
		//case KeyboardKey::eK:
		//	myPitchBackward = false;
		//	break;
		//case KeyboardKey::eT:
		//	myMoveUp = false;
		//	break;
		//case KeyboardKey::eG:
		//	myMoveDown = false;
		//	break;
		//case KeyboardKey::eF:
		//	myMoveLeft = false;
		//	break;
		//case KeyboardKey::eH:
		//	myMoveRight = false;
		//	break;
		//default:
		//	break;
		//}

		return ReceiveResult::eContinue;
	}

	ENGINE_NAMESPACE::ReceiveResult BouncingComponent::Receive(const AnyKeyDownMessage & aMessage)
	{

		//switch (aMessage.key)
		//{
		//case KeyboardKey::eU:
		//	myRollLeft = true;
		//	break;
		//case KeyboardKey::eO:
		//	myRollRight = true;
		//	break;
		//case KeyboardKey::eJ:
		//	myRotateLeft = true;
		//	break;
		//case KeyboardKey::eL:
		//	myRotateRight = true;
		//	break;
		//case KeyboardKey::eI:
		//	myPitchForward = true;
		//	break;
		//case KeyboardKey::eK:
		//	myPitchBackward = true;
		//	break;
		//case KeyboardKey::eT:
		//	myMoveUp = true;
		//	break;
		//case KeyboardKey::eG:
		//	myMoveDown = true;
		//	break;
		//case KeyboardKey::eF:
		//	myMoveLeft = true;
		//	break;
		//case KeyboardKey::eH:
		//	myMoveRight = true;
		//	break;
		//default:
		//	break;
		//}

		return ReceiveResult::eContinue;
	}

	/*
		void BouncingComponent::RotateWithKeys(const Time & aDeltaTime)
		{
			const float RotationSpeed = DEGREES_TO_RADIANSF(10.f);
			if (myRollLeft)
			{
				myObject->GetRotation().RotateAroundLocalZ(-RotationSpeed * aDeltaTime.InSeconds());
			}
			if (myRollRight)
			{
				myObject->GetRotation().RotateAroundLocalZ(RotationSpeed * aDeltaTime.InSeconds());
			}
			if (myPitchForward)
			{
				myObject->GetRotation().RotateAroundLocalX(RotationSpeed * aDeltaTime.InSeconds());
			}
			if (myPitchBackward)
			{
				myObject->GetRotation().RotateAroundLocalX(-RotationSpeed * aDeltaTime.InSeconds());
			}
			if (myRotateLeft)
			{
				myObject->GetRotation().RotateAroundLocalY(RotationSpeed * aDeltaTime.InSeconds());
			}
			if (myRotateRight)
			{
				myObject->GetRotation().RotateAroundLocalY(-RotationSpeed * aDeltaTime.InSeconds());
			}
		}


		void BouncingComponent::MoveObjectPosition(const Time & aDeltaTime)
		{
			const float MovementSpeed = 10.f * aDeltaTime.InSeconds();

			if (myMoveLeft)
			{
				myObject->SetPosition(myObject->GetPosition() + myObject->GetRotation().GetLeft() * MovementSpeed);
			}
			if (myMoveRight)
			{
				myObject->SetPosition(myObject->GetPosition() + myObject->GetRotation().GetRight() * MovementSpeed);
			}
			if (myMoveUp)
			{
				myObject->SetPosition(myObject->GetPosition() + myObject->GetRotation().GetUpward() * MovementSpeed);
			}
			if (myMoveDown)
			{
				myObject->SetPosition(myObject->GetPosition() + myObject->GetRotation().GetDownward() * MovementSpeed);
			}
		}

		void BouncingComponent::MoveObjectWorldPosition(const Time & aDeltaTime)
		{
			const float MovementSpeed = 10.f * aDeltaTime.InSeconds();

			if (myMoveLeft)
			{
				myObject->SetPosition(myObject->GetPosition() + Vector3f(-1.f, 0.f, 0.f) * MovementSpeed);
			}
			if (myMoveRight)
			{
				myObject->SetPosition(myObject->GetPosition() + Vector3f(1.f, 0.f, 0.f) * MovementSpeed);
			}
			if (myMoveUp)
			{
				myObject->SetPosition(myObject->GetPosition() + Vector3f(0.f, 1.f, 0.f) * MovementSpeed);
			}
			if (myMoveDown)
			{
				myObject->SetPosition(myObject->GetPosition() + Vector3f(0.f, -1.f, 0.f) * MovementSpeed);
			}
		}*/
}
