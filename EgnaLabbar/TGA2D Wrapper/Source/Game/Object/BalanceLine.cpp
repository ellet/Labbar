#include "stdafx.h"
#include "BalanceLine.h"
#include <Macros/Macros.h>
#include "Object.h"
#include <Matriser/matrix33.h>

const float maxAngle = DEGRESS_TO_RADIANSF(45.f);

Vector2f VictoryAngle::VictoryAngleDistanceOffset;


//BalanceLine::BalanceLine()
//{
//	LoadSprite("Sprites/TestSprites/BalanceBeam.dds");
//
//	SetPosition(Vector2f(450.f, 500.f));
//	SetPivot(Vector2f(0.5f, 0.5f));
//
//	myCurrentAngle = 0.f;
//
//#pragma region WeightsSetup
//
//	myLeftWeights.Init(10);
//
//	Vector2f aLeftTempPosition = GetPosition() - Vector2f(100.f, 0.f);
//
//	myLeftWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(12.f), aLeftTempPosition, Vector2f(75.f, 0.f)));
//	myLeftWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(27.f), aLeftTempPosition, Vector2f(0.f, 0.f)));
//	myLeftWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(7.32f), aLeftTempPosition, Vector2f(-75.f, 0.f)));
//
//
//	myRightWeights.Init(10);
//
//	Vector2f aRightTempPosition = GetPosition() + Vector2f(100.f, 0.f);
//
//	myRightWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(32.f), aRightTempPosition, Vector2f(0.f, 0.f)));
//	myRightWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(38.f), aRightTempPosition, Vector2f(75.f, 0.f)));
//
//#pragma endregion
//
//#pragma region VictoryAnglesSetup
//
//	myVictoryAngles.Init(10);
//	VictoryAngle::VictoryAngleDistanceOffset = Vector2f(0.f, 300.f);
//
//	myVictoryAngles.Add(new VictoryAngle(GetPosition(), DEGRESS_TO_RADIANSF(0.f)));
//	myVictoryAngles.Add(new VictoryAngle(GetPosition(), DEGRESS_TO_RADIANSF(32.f)));
//	myVictoryAngles.Add(new VictoryAngle(GetPosition(), DEGRESS_TO_RADIANSF(-12.f)));
//
//#pragma endregion
//
//	myBalanceSpeed = 0.5f;
//}

BalanceLine::BalanceLine(const BeamData & aBeamData)
{
	LoadSprite(aBeamData.mySpritePath.c_str());

	SetPosition(aBeamData.myMainPoint);
	SetPivot(Vector2f(0.5f, 0.5f));

	myCurrentAngle = 0.f;

#pragma region WeightsSetup

	myLeftWeights.Init(aBeamData.myLeftSideWeights.Size());

	myRightSideOffset = aBeamData.myRightSideOffset;
	myLeftSideOffset = aBeamData.myLeftSideOffset;

	Vector2f aLeftTempPosition = GetPosition() - myLeftSideOffset;

	for (unsigned short iLeftSide = 0; iLeftSide < aBeamData.myLeftSideWeights.Size(); ++iLeftSide)
	{
		myLeftWeights.Add(new OnOffWeigth(aBeamData.myLeftSideWeights[iLeftSide], aLeftTempPosition));
	}

	/*myLeftWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(12.f), aLeftTempPosition, Vector2f(75.f, 0.f)));
	myLeftWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(27.f), aLeftTempPosition, Vector2f(0.f, 0.f)));
	myLeftWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(7.32f), aLeftTempPosition, Vector2f(-75.f, 0.f)));*/


	myRightWeights.Init(10);

	Vector2f aRightTempPosition = GetPosition() + myRightSideOffset;

	for (unsigned short iRightSide = 0; iRightSide < aBeamData.myRightSideWeights.Size(); ++iRightSide)
	{
		myRightWeights.Add(new OnOffWeigth(aBeamData.myRightSideWeights[iRightSide], aRightTempPosition));
	}

	/*myRightWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(32.f), aRightTempPosition, Vector2f(0.f, 0.f)));
	myRightWeights.Add(new OnOffWeigth(DEGRESS_TO_RADIANSF(38.f), aRightTempPosition, Vector2f(75.f, 0.f)));*/

#pragma endregion

#pragma region VictoryAnglesSetup

	myVictoryAngles.Init(aBeamData.myVictoryAngles.Size());
	VictoryAngle::VictoryAngleDistanceOffset = Vector2f(0.f, aBeamData.VictoryPointDistanceFromLine);

	for (unsigned short iVictoryAngle = 0; iVictoryAngle < aBeamData.myVictoryAngles.Size(); ++iVictoryAngle)
	{
		myVictoryAngles.Add(new VictoryAngle(*aBeamData.myVictoryAngles[iVictoryAngle], GetPosition()));
	}

	/*myVictoryAngles.Add(new VictoryAngle(GetPosition(), DEGRESS_TO_RADIANSF(0.f)));
	myVictoryAngles.Add(new VictoryAngle(GetPosition(), DEGRESS_TO_RADIANSF(32.f)));
	myVictoryAngles.Add(new VictoryAngle(GetPosition(), DEGRESS_TO_RADIANSF(-12.f)));*/

#pragma endregion

	myBalanceSpeed = 0.5f;
}

BalanceLine::~BalanceLine()
{
	
}

void BalanceLine::Update(const float aDeltaTime)
{
#pragma region Calculate Goal Angle
	float goalAngle = 0.f;
	float rightSideAngle = 0.f;
	float leftSideAngle = 0.f;

	for (unsigned short iWeight = 0; iWeight < myRightWeights.Size(); ++iWeight)
	{
		if (myRightWeights[iWeight]->GetLiftedState() == false)
		{
			rightSideAngle += myRightWeights[iWeight]->GetAngleWeight();
		}
	}

	for (unsigned short iWeight = 0; iWeight < myLeftWeights.Size(); ++iWeight)
	{
		if (myLeftWeights[iWeight]->GetLiftedState() == false)
		{
			leftSideAngle += myLeftWeights[iWeight]->GetAngleWeight();
		}
	}

	goalAngle = rightSideAngle - leftSideAngle;

#pragma endregion

#pragma region Clamp GoalAngle
	if ((SIGN(goalAngle) * goalAngle) > maxAngle)
	{
		goalAngle = SIGN(goalAngle) * maxAngle;
	}
#pragma endregion

#pragma region Change Current Angle
	float tempSpeed = myBalanceSpeed * aDeltaTime;

	if (goalAngle != myCurrentAngle)
	{
		if (goalAngle > myCurrentAngle + tempSpeed)
		{
			myCurrentAngle += tempSpeed;
		}
		else if (goalAngle < myCurrentAngle - tempSpeed)
		{
			myCurrentAngle -= tempSpeed;
		}
		else
		{
			myCurrentAngle = goalAngle;
			for (unsigned short iVictory = 0; iVictory < myVictoryAngles.Size(); ++iVictory)
			{
				if (myVictoryAngles[iVictory]->myAngleThatNeedsToBeAchieved == myCurrentAngle)
				{
					myVictoryAngles[iVictory]->myIhaveBeenAchieved = true;
					myVictoryAngles[iVictory]->TriggerOnUse();
				}
			}
		}
	}
#pragma endregion

#pragma region Update Weights

	Vector2f aLeftTempPosition = GetPosition() - (myLeftSideOffset * Matrix33f::CreateRotateAroundZ(myCurrentAngle));

	for (unsigned short iWeight = 0; iWeight < myLeftWeights.Size(); ++iWeight)
	{
		myLeftWeights[iWeight]->Update(aDeltaTime, aLeftTempPosition, myCurrentAngle);
	}

	Vector2f aRightTempPosition = GetPosition() + (myRightSideOffset * Matrix33f::CreateRotateAroundZ(myCurrentAngle));

	for (unsigned short iWeight = 0; iWeight < myRightWeights.Size(); ++iWeight)
	{
		myRightWeights[iWeight]->Update(aDeltaTime, aRightTempPosition, myCurrentAngle);
	}

#pragma endregion

#pragma region Update Victory
	for (unsigned short iVictory = 0; iVictory < myVictoryAngles.Size(); ++iVictory)
	{
		myVictoryAngles[iVictory]->Update(aDeltaTime);
	}
#pragma endregion

	SetRotation(myCurrentAngle);
}

void BalanceLine::Draw() const
{
#pragma region Draw Weights

	BaseGameObject::Draw();

	for (unsigned short iWeight = 0; iWeight < myRightWeights.Size(); ++iWeight)
	{
		myRightWeights[iWeight]->Draw();
	}

	for (unsigned short iWeight = 0; iWeight < myLeftWeights.Size(); ++iWeight)
	{
		myLeftWeights[iWeight]->Draw();
	}

#pragma endregion

#pragma region Draw VictoryAngles
	for (unsigned short iVictoryAngle = 0; iVictoryAngle < myVictoryAngles.Size(); ++iVictoryAngle)
	{
		myVictoryAngles[iVictoryAngle]->Draw();
	}
#pragma endregion
}

