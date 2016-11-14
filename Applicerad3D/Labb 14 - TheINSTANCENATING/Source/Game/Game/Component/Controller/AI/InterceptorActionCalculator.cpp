#include "stdafx.h"
#include "InterceptorActionCalculator.h"
#include "AIInterceptorComponent.h"
#include "..\Utilities\Utilities\Math\MathMacros.h"
#include "..\Engine\Engine\Physics\PhysicsComponent.h"
#include <Engine\Component\Collider\ColliderComponent.h>

InterceptorActionCalculator::InterceptorActionCalculator()
{
	myPlayer = nullptr;
	myInterceptor = nullptr;
	myDistanceToPlayerUntilRotate = 0.0f;
	myRotateTowardsPlayerPoints = 0;
	myIsRotatingPoints = 0;
	myShootAtPlayerPoints = 0;
	myTurnAwayFromClusterPoints = 0;
	myTurnAwayFromObjectPoints = 0;
}

InterceptorActionCalculator::~InterceptorActionCalculator()
{
}

ActionScoreResult InterceptorActionCalculator::CalculateActionScore(AIInterceptorComponent * aInterceptor)
{
	InterceptorActionScores scores;
	scores.myAccelerate = ActionScore{ ActionScoreResult::eAccelerate, 0 };
	scores.myTurnAwayFromPlayer = ActionScore{ ActionScoreResult::eTurnAwayFromPlayer, 0 };
	scores.myRotateTowardsPlayer = ActionScore{ ActionScoreResult::eRotateTowardsPlayer, 0 };
	scores.myShootAtPlayer = ActionScore{ ActionScoreResult::eShootAtPlayer, 0 };
	scores.myTurnAwayFromPoint = ActionScore{ ActionScoreResult::eTurnAwayFromPoint, 0 };

	SB::Vector3f dirToPlayer = myPlayer->GetPosition() - myInterceptor->GetPosition();
	aInterceptor->myDistanceToPlayer = (dirToPlayer).Length();
	dirToPlayer.Normalize();
	aInterceptor->myAngleToPlayer = RADIANS_TO_DEGREESF(SB::Vector3f::GetAngleBetween(myInterceptor->GetRotation().GetForward(), (myInterceptor->GetPosition() - myPlayer->GetPosition())));
	if (dirToPlayer.z * myInterceptor->GetRotation().GetForward().z < 0)
	{
		aInterceptor->myAngleToPlayer = 180 - aInterceptor->myAngleToPlayer;
	}
	CalculateAccelerationScore(aInterceptor, scores);
	CalculateTurnAwayFromPlayerScore(aInterceptor, scores);
	CalculateTurnAwayFromPoint(aInterceptor, scores);
	CalculateRotateTowardsPlayerScore(aInterceptor, scores);
	CalculateShootAtPlayerScore(aInterceptor, scores);

	return CalculateResult(scores);
}

void InterceptorActionCalculator::CalculateAccelerationScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	myInterceptor->GetComponent<SB::PhysicsComponent>()->SetDrag(0.f);

	aActionScores.myAccelerate.myValue += static_cast<int>(600.f * ( 1.f - (aInterceptor->myForwardCurrentSpeed / aInterceptor->myForwardMaxSpeed )));
	if (aInterceptor->myForwardCurrentSpeed < aInterceptor->myForwardMaxSpeed)
	{
		aActionScores.myAccelerate.myValue += 50;
	}
}

void InterceptorActionCalculator::CalculateTurnAwayFromPoint(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	SB::GrowingArray<const SB::GameObject*> & nearbyObjects = aInterceptor->myNearbyObjects;
	SB::Vector3f objClusterCenter;
	
	SB::Vector3f interceptorPos = myInterceptor->GetPosition();
	SB::Vector3f closestPoint = SB::Vector3f::Zero;
	float distToClosestPoint = 100000.f;
	aInterceptor->myDistanceToNearestPoint = 10000.f;
	float closestAngle = 90.f;
	SB::Vector3f dirToObject;
	for (unsigned short i = 0; i < nearbyObjects.Size(); i++)
	{
		objClusterCenter += nearbyObjects[i]->GetPosition();
		float distToPoint = (nearbyObjects[i]->GetPosition() - interceptorPos).Length2();
		if (distToPoint < 60.f*60.f)
		{
			dirToObject = myInterceptor->GetPosition() - nearbyObjects[i]->GetPosition();
			dirToObject.Normalize();
			if (WillHitObject(aInterceptor, nearbyObjects[i]) == true)
			{
				if (distToPoint < distToClosestPoint)
				{
					closestPoint = nearbyObjects[i]->GetPosition();
					distToClosestPoint = distToPoint;
				}
			}
		}
	}
	objClusterCenter /= nearbyObjects.Size();
	aInterceptor->myTurnAwayFromCluster = objClusterCenter;

	if (closestPoint != SB::Vector3f::Zero)
	{
		aInterceptor->myDistanceToNearestPoint = distToClosestPoint;
		aActionScores.myTurnAwayFromPoint.myValue += myTurnAwayFromObjectPoints;
		aInterceptor->myTurnAwayFromObject = closestPoint;
		aInterceptor->myIsTurning = false;
		return;
	}
	else if (aInterceptor->myIsTurning == false)
	{
		aInterceptor->myTurnAwayFromCluster = objClusterCenter;
	}
	else if ((objClusterCenter - aInterceptor->myTurnAwayFromCluster).Length2() > 30.f*30.f)
	{
		aInterceptor->myTurnAwayFromCluster = objClusterCenter;
		aInterceptor->myIsTurning = false;
	}

	if ((objClusterCenter - interceptorPos).Length2() <150.f*150.f)
	{
		aActionScores.myTurnAwayFromPoint.myValue += myTurnAwayFromClusterPoints;
		aActionScores.myTurnAwayFromPoint.myValue += 2 * nearbyObjects.Size();
	}
}

void InterceptorActionCalculator::CalculateTurnAwayFromPlayerScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	if (aInterceptor->myAngleToPlayer > 90)
	{
		aActionScores.myTurnAwayFromPlayer.myValue += -100;
	}
	else if (aInterceptor->myDistanceToPlayer < 150.f)
	{
		aActionScores.myTurnAwayFromPlayer.myValue += static_cast<int>(75.f + (150.f - aInterceptor->myDistanceToPlayer));
	}
}

void InterceptorActionCalculator::CalculateRotateTowardsPlayerScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	if (aInterceptor->myDistanceToPlayer > myDistanceToPlayerUntilRotate && aInterceptor->myForwardCurrentSpeed > aInterceptor->myForwardMaxSpeed / 2.f
		&& aInterceptor->myAngleToPlayer > 30.f)
	{
		aActionScores.myRotateTowardsPlayer.myValue += myRotateTowardsPlayerPoints;
	}

	if (aInterceptor->myAngleToPlayer < 1.f)
	{
		aInterceptor->myIsRotating = false;
	}
	if (aInterceptor->myIsRotating == true)
	{
		aActionScores.myRotateTowardsPlayer.myValue += myIsRotatingPoints;
	}
}

void InterceptorActionCalculator::CalculateShootAtPlayerScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	if (aInterceptor->myAngleToPlayer < 10.f)
	{
		aActionScores.myShootAtPlayer.myValue += myShootAtPlayerPoints;
	}
}

ActionScoreResult InterceptorActionCalculator::CalculateResult(InterceptorActionScores & aActionScores)
{
	ActionScore result = { ActionScoreResult::eNoAction , 0 };
	if (result.myValue < aActionScores.myAccelerate.myValue)
	{
		result = aActionScores.myAccelerate;
	}
	if (result.myValue < aActionScores.myTurnAwayFromPlayer.myValue)
	{
		result = aActionScores.myTurnAwayFromPlayer;
	}
	if (result.myValue < aActionScores.myRotateTowardsPlayer.myValue)
	{
		result = aActionScores.myRotateTowardsPlayer;
	}
	if (result.myValue < aActionScores.myShootAtPlayer.myValue)
	{
		result = aActionScores.myShootAtPlayer;
	}
	if (result.myValue < aActionScores.myTurnAwayFromPoint.myValue)
	{
		result = aActionScores.myTurnAwayFromPoint;
	}

	return result.myResult;
}

void InterceptorActionCalculator::SetObjects(SB::GameObject* aPlayer, SB::GameObject* aInterceptor)
{
	myPlayer = aPlayer;
	myInterceptor = aInterceptor;
}

float InterceptorActionCalculator::GetAngleToAvoidObject(AIInterceptorComponent * aInterceptor, const SB::GameObject* aGameObject)
{
	SB::Vector3f interceptorPos = myInterceptor->GetPosition();
	SB::Vector3f projectedPos = interceptorPos + myInterceptor->GetRotation().GetForward() * aInterceptor->myForwardCurrentSpeed;
	SB::Vector3f distBetweenPos = projectedPos - aGameObject->GetPosition();
	SB::Vector3f dirToOutsideCollider;
	SB::Vector3f dirToObject = distBetweenPos.Normalize();
	SB::Vector3f perp = SB::Vector3f::Cross(dirToObject, dirToObject + SB::Vector3f(0.5f, 0.0f, 0.0f));
	SB::Vector3f pointOutsideCollider = aGameObject->GetPosition() + perp * (aGameObject->GetComponent<SB::ColliderComponent>()->GetCollider().GetRadius() + 10.f);
	dirToOutsideCollider = pointOutsideCollider - interceptorPos;
	dirToOutsideCollider.Normalize();
	return RADIANS_TO_DEGREESF(SB::Vector3f::GetAngleBetween(myInterceptor->GetRotation().GetForward().GetNormalized(), dirToOutsideCollider));
}

bool InterceptorActionCalculator::WillHitObject(AIInterceptorComponent * aInterceptor, const SB::GameObject* aGameObject)
{
	//Bad replacement for ray tracing
	if (aGameObject->GetComponent<SB::ColliderComponent>() == nullptr)
	{
		return false;
	}
	const SB::Vector3f & interceptorPos = myInterceptor->GetPosition();

	const SB::Vector3f & direction = myInterceptor->GetRotation().GetForward();

	float interceptorRadius = aGameObject->GetComponent<SB::ColliderComponent>()->GetCollider().GetRadius();
	SB::Vector3f projectedPos = interceptorPos + direction * aInterceptor->myForwardCurrentSpeed;
	SB::Vector3f distBetweenPos = projectedPos - aGameObject->GetPosition();
	
	float objectRadius = (aGameObject->GetComponent<SB::ColliderComponent>()->GetCollider().GetRadius());
	if ((distBetweenPos.Length() - interceptorRadius) < objectRadius)
	{
		return true;
	}
	projectedPos = interceptorPos + myInterceptor->GetRotation().GetLeft() * interceptorRadius + direction * aInterceptor->myForwardCurrentSpeed;
	distBetweenPos = projectedPos - aGameObject->GetPosition();

	if ((distBetweenPos.Length() - interceptorRadius) < objectRadius)
	{
		return true;
	}
	projectedPos = interceptorPos + myInterceptor->GetRotation().GetRight() * interceptorRadius + direction * aInterceptor->myForwardCurrentSpeed;
	distBetweenPos = projectedPos - aGameObject->GetPosition();

	if ((distBetweenPos.Length() - interceptorRadius) < objectRadius)
	{
		return true;
	}
	return false;
}

void InterceptorActionCalculator::LoadData(SB::DataNode aProperties)
{
	myDistanceToPlayerUntilRotate = aProperties["distanceToPlayerUntilRotate"].GetFloat();
	myRotateTowardsPlayerPoints = aProperties["rotateTowardsPlayerPoints"].GetInt();
	myIsRotatingPoints = aProperties["isRotatingPoints"].GetInt();
	myShootAtPlayerPoints = aProperties["shootAtPlayerPoints"].GetInt();
	myTurnAwayFromClusterPoints = aProperties["turnAwayFromClusterPoints"].GetInt();
	myTurnAwayFromObjectPoints = aProperties["turnAwayFromObjectPoints"].GetInt();
}

void InterceptorActionCalculator::ToJson()const
{
	SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();

	serializer.WriteNode("distanceToPlayerUntilRotate", myDistanceToPlayerUntilRotate);
	serializer.WriteNode("rotateTowardsPlayerPoints", myRotateTowardsPlayerPoints);
	serializer.WriteNode("isRotatingPoints", myIsRotatingPoints);
	serializer.WriteNode("shootAtPlayerPoints", myShootAtPlayerPoints);
	serializer.WriteNode("turnAwayFromClusterPoints", myTurnAwayFromClusterPoints);
	serializer.WriteNode("turnAwayFromObjectPoints", myTurnAwayFromObjectPoints);
}
