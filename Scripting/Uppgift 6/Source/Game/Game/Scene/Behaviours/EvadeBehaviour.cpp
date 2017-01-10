#include "stdafx.h"
#include "EvadeBehaviour.h"
#include "..\TheLabs\Unit.h"

const float EvadeRadius = 95.f;

const float WallExtraWeight = 1.f;

//const float EvadeWeight = 1.f;

float EvadeBehaviour::ourMaxWeight = 5.f;

float EvadeBehaviour::ourEvadeWeight = 1.f;

EvadeBehaviour::EvadeBehaviour(const Unit & aParentUnit) : BaseBehaviour(aParentUnit)
{
}


EvadeBehaviour::~EvadeBehaviour()
{
}

Steering EvadeBehaviour::GetSteering(const SB::Time & aDeltaTime)
{
	if (myUpdateTimer.GetElapsedTime().InSeconds() < 0.1f)
	{
		return mySteering;
	}

	myWeight = ourMaxWeight;

	myUpdateTimer.Restart();
	mySteering = Steering();

	Steering currentSterring = mySteering;
	HandleWalls(currentSterring);

	/*for (unsigned short iPoint = 0; iPoint < myPointsToEvade.Size(); ++iPoint)
	{
		HandleEvadePoint(myPointsToEvade[iPoint], currentSterring);
	}*/


	if (myPointsToEvade.Size() > 0)
	{
		SB::Vector2f closestPoint;
		float closestDistance = 100000.f;

		for (unsigned short iPoint = 0; iPoint < myPointsToEvade.Size(); ++iPoint)
		{
			const float CurrentDistance = (myPointsToEvade[iPoint] - myParentUnit->GetPosition()).Length();
			if (closestDistance > CurrentDistance)
			{
				closestDistance = CurrentDistance;
				closestPoint = myPointsToEvade[iPoint];
			}
		}

		HandleEvadePoint(closestPoint, currentSterring);
	}
	

	if (currentSterring.Direction.Length() > myWeight)
	{
		currentSterring.Direction = currentSterring.Direction.GetNormalized() * myWeight;
	}

	myPointsToEvade.RemoveAll();


	mySteering = currentSterring;
	return currentSterring;
}

void EvadeBehaviour::AddAvoidPosition(const SB::Vector2f & aPositionToEvade)
{
	myPointsToEvade.Add(aPositionToEvade);
}

float EvadeBehaviour::GetEvadeRadius()
{
	return EvadeRadius;
}



void EvadeBehaviour::HandleWalls(Steering & aSterringToSet)
{
	const SB::Vector2f & CurrentPosition = myParentUnit->GetPosition();

	if (CurrentPosition.x < EvadeRadius)
	{
		const float ExtraWeight = 1.f - (CurrentPosition.x / EvadeRadius);
		aSterringToSet.Direction += SB::Vector2f::UnitX * (WallExtraWeight * ExtraWeight);
		aSterringToSet.SpeedPercentage = 1.f;
	}
	else if (CurrentPosition.x > 1920.f - EvadeRadius)
	{
		const float ExtraWeight = 1.f - (std::abs( CurrentPosition.x - 1920.f)/ EvadeRadius);
		aSterringToSet.Direction -= SB::Vector2f::UnitX * (WallExtraWeight * ExtraWeight);
		aSterringToSet.SpeedPercentage = 1.f;
	}

	if (CurrentPosition.y < EvadeRadius)
	{
		const float ExtraWeight = 1.f - (CurrentPosition.y / EvadeRadius);
		aSterringToSet.Direction += SB::Vector2f::UnitY * (WallExtraWeight * ExtraWeight);
		aSterringToSet.SpeedPercentage = 1.f;
	}
	else if (CurrentPosition.y > 1080.f - EvadeRadius)
	{
		const float ExtraWeight = 1.f - (std::abs(CurrentPosition.y - 1080.f) / EvadeRadius);
		aSterringToSet.Direction -= SB::Vector2f::UnitY * (WallExtraWeight * ExtraWeight);
		aSterringToSet.SpeedPercentage = 1.f;
	}
}

void EvadeBehaviour::HandleEvadePoint(const SB::Vector2f & aPointToEvade, Steering & aSterringToSet)
{
	SB::Vector2f directionVector = myParentUnit->GetPosition() - aPointToEvade;
	float ClosenessWeight = 1.f - (directionVector.Length() / EvadeRadius);

	if (ClosenessWeight < 0.f)
	{
		ClosenessWeight = -ClosenessWeight;
	}


	aSterringToSet.Direction += ClosenessWeight * ourEvadeWeight * directionVector.GetNormalized();
	aSterringToSet.SpeedPercentage = 1.f;

}
