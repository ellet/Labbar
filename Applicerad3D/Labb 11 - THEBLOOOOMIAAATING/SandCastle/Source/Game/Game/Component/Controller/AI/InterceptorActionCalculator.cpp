#include "stdafx.h"
#include "InterceptorActionCalculator.h"
#include "AIInterceptorComponent.h"
#include "..\Utilities\Utilities\Math\MathMacros.h"

InterceptorActionCalculator::InterceptorActionCalculator()
{
}

InterceptorActionCalculator::~InterceptorActionCalculator()
{
}

ActionScoreResult InterceptorActionCalculator::CalculateActionScore(AIInterceptorComponent * aInterceptor)
{
	InterceptorActionScores scores;
	scores.myAccelerate = ActionScore{ ActionScoreResult::eAccelerate, 0 };
	scores.myStartToBreak = ActionScore{ ActionScoreResult::eStartToBreak, 0 };
	scores.myTurnAwayFromPlayer = ActionScore{ ActionScoreResult::eTurnAwayFromPlayer, 0 };
	scores.myRotateTowardsPlayer = ActionScore{ ActionScoreResult::eRotateTowardsPlayer, 0 };
	scores.myShootAtPlayer = ActionScore{ ActionScoreResult::eShootAtPlayer, 0 };
	scores.myTurnAwayFromPoint = ActionScore{ ActionScoreResult::eTurnAwayFromPoint, 0 };

	SB::Vector3f dirToPlayer = myPlayer->GetPosition() - myInterceptor->GetPosition();
	aInterceptor->myDistanceToPlayer = (dirToPlayer).Length();
	dirToPlayer.Normalize();
	aInterceptor->myAngleToPlayer = RADIANS_TO_DEGRESSF(SB::Vector3f::GetAngleBetween(myInterceptor->GetRotation().GetForward(), (myInterceptor->GetPosition() - myPlayer->GetPosition())));
	if (dirToPlayer.z * myInterceptor->GetRotation().GetForward().z < 0)
	{
		aInterceptor->myAngleToPlayer = 180 - aInterceptor->myAngleToPlayer;
	}

	//break
	scores.myStartToBreak.myValue += static_cast<int>CLAMP((30.f - aInterceptor->myDistanceToPlayer) * 5.f, 0.f, 100.f);

	CalculateAccelerationScore(aInterceptor, scores);
	CalculateTurnAwayFromPlayerScore(aInterceptor, scores);
	CalculateTurnAwayFromPoint(aInterceptor, scores);
	CalculateRotateTowardsPlayerScore(aInterceptor, scores);
	CalculateShootAtPlayerScore(aInterceptor, scores);

	return CalculateResult(scores);
}

void InterceptorActionCalculator::CalculateAccelerationScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	if (aInterceptor->myForwardCurrentSpeed < aInterceptor->myForwardMaxSpeed && aInterceptor->myAngleToPlayer > 90)
	{
		aActionScores.myAccelerate.myValue += 200;
	}
	if (aInterceptor->myForwardCurrentSpeed < aInterceptor->myForwardMaxSpeed / 5.f)
	{
		aActionScores.myAccelerate.myValue += 200;
	}
	if (aInterceptor->myForwardCurrentSpeed < aInterceptor->myForwardMaxSpeed)
	{
		aActionScores.myAccelerate.myValue += 50;
	}
}

void InterceptorActionCalculator::CalculateTurnAwayFromPoint(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	SB::GrowingArray<const SB::GameObject*> & nearbyObjects = aInterceptor->myNearbyObjects;
	SB::Vector3f objClusterCenter =  SB::Vector3f::Zero;

	for (unsigned short i = 0; i < nearbyObjects.Size(); i++)
	{
		objClusterCenter += nearbyObjects[i]->GetPosition();
	}
	objClusterCenter /= nearbyObjects.Size();
	if (aInterceptor->myIsTurning == false)
	{
		aInterceptor->myTurnAwayFromPoint = objClusterCenter;
	}
	else if ((objClusterCenter - aInterceptor->myTurnAwayFromPoint).Length2() > 20*20)
	{
		aInterceptor->myTurnAwayFromPoint = objClusterCenter;
		aInterceptor->myIsTurning = false;
	}
	if ((objClusterCenter - myInterceptor->GetPosition()).Length2() < 22500.f)
	{
		aActionScores.myTurnAwayFromPoint.myValue += 50;
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
		aActionScores.myTurnAwayFromPlayer.myValue += static_cast<int>(25.f + (150.f - aInterceptor->myDistanceToPlayer));
	}
}

void InterceptorActionCalculator::CalculateRotateTowardsPlayerScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	if (aInterceptor->myDistanceToPlayer > 300.f && aInterceptor->myForwardCurrentSpeed > aInterceptor->myForwardMaxSpeed / 2.f
		&& aInterceptor->myAngleToPlayer > 30.f)
	{
		aActionScores.myRotateTowardsPlayer.myValue += 200;
	}

	if (aInterceptor->myAngleToPlayer < 1.f)
	{
		aInterceptor->myIsRotating = false;
	}
	if (aInterceptor->myIsRotating == true)
	{
		aActionScores.myRotateTowardsPlayer.myValue += 100;
	}
}

void InterceptorActionCalculator::CalculateShootAtPlayerScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores)
{
	if (aInterceptor->myAngleToPlayer < 10.f)
	{
		aActionScores.myShootAtPlayer.myValue += 75;
	}
}

ActionScoreResult InterceptorActionCalculator::CalculateResult(InterceptorActionScores & aActionScores)
{
	ActionScore result = { ActionScoreResult::eNoAction , 0 };

	if (result.myValue < aActionScores.myStartToBreak.myValue)
	{
		result = aActionScores.myStartToBreak;
	}
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
