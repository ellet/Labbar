#include "stdafx.h"
#include "Player.h"
#include <Utility/TGA2DConversions.h>
#include <iostream>
#include "../TGA2DWrapper/RendererManager/RenderManager.h"
#include <math.h>
#include <Intersection/Intersection2D.h>

const std::string AnimationWalkingDirections[] = {
	"walkingLeft", "walkingUpLeft",
	"walkingUp", "walkingUpRight",
	"walkingRight", "walkingDownRight",
	"walkingDown", "walkingDownLeft"
};
const std::string AnimationIdleDirections[] = {
	"idleLeft", "idleUpLeft",
	"idleUp", "idleUpRight",
	"idleRight", "idleDownRight",
	"idleDown", "idleDownLeft"
};

Player::Player()
	: myScaleConstant(1.f), myScaleSlope(0.f), myAnimationDirection(0)
{
	SetPivot(Vector2f(0.5f, 0.9f));
	myBordersToCheck.Init(10);
	mySpeed = 200.f;
	myWayPoints.Init(1);
}

void Player::Init(CommonUtilities::GrowingArray<Border> aBorderList)
{
	if (myBordersToCheck.IsInitialized() == false)
	{
		myBordersToCheck.Init(aBorderList.Size());
	}
	
	myBordersToCheck = aBorderList;
	myWayPoints.Add(GetPosition());

}

void Player::UpdateBorders(CommonUtilities::GrowingArray<Border> aBorderList)
{
	//Will only be used for editing
	myBordersToCheck = aBorderList;
}

void Player::SetGotoPosition(Vector2f aGotoPosition)
{

	if (aGotoPosition.x < 0.f || aGotoPosition.x > 1920.f)
	{
		return;
	}
	if (aGotoPosition.y < 0.f || aGotoPosition.y > 1080.f)
	{
		return;
	}
	if (GetDistance(GetPosition(), aGotoPosition) < 40.f)
	{
		return;
	}

	//User clicked, set position.
	myGotoPosition = aGotoPosition;
	FindPath(myDeltaTime);

	const float pi = 3.14159265f;
	const float slicedHalfDirection = pi / 8.f;
	const float direction = std::atan2(myVelocity.y, myVelocity.x) + pi;

	myAnimationDirection = static_cast<size_t>(direction / slicedHalfDirection + 1) / 2;
	if (myAnimationDirection == 8)
	{
		myAnimationDirection = 0;
	}

	SetDefaultAnimation(AnimationIdleDirections[myAnimationDirection]);

}
void Player::ResetGoto()
{
	myVelocity = Vector2f::Zero;
	StopAnimation();
}

void Player::SetSpeed(float aSpeed)
{
	mySpeed = aSpeed;
}

void Player::Update(const float aDeltaTime)
{

	float height = GetPosition().y;
	float scale = myScaleConstant + height * myScaleSlope;

	BaseAnimatedGameObject::Update(aDeltaTime);

	//Vector2f tempVector; 
	//float value = sqrt(pow((myBordersToCheck[0].GetNode2().x - myBordersToCheck[0].GetNode1().x), 2) + pow((myBordersToCheck[0].GetNode2().y - myBordersToCheck[0].GetNode1().y), 2))
	//tempVector = Vector2f(myBordersToCheck[4].GetNode2().GetNormalized().x + myBordersToCheck[4].GetNode1().GetNormalized().x,
	//tempVector.Normalize();
	//RenderManager::AddRenderCommandLine(RenderCommandLine(myBordersToCheck[4].GetNode1(), tempVector, Vector4f(0,1,0,1)));

	if (myVelocity != Vector2f::Zero)
	{

		Vector2f position = GetPosition() + (myVelocity * aDeltaTime * scale);

		myDeltaTime = aDeltaTime;
		for (unsigned short i = 0; i < myBordersToCheck.Size(); i++)
		{
			Vector2f intersection;
			if (BorderIntersect(myBordersToCheck[i], GetPosition(), position, intersection) == true)
			{
				myVelocity.x = 0;
				myVelocity.y = 0;
				position = GetPosition();
			}
		}
		//Distance to gotoPosition, and how far away it will stop.
		if (GetDistance(GetPosition(), myGotoPosition) < 10.f)
		{
			myVelocity.x = 0;
			myVelocity.y = 0;
		}

		SetPosition(position);

		myRenderPriority = position.y;

		if (myVelocity == Vector2f::Zero)
		{
			StopAnimation();
		}
		else
		{
			PlayAnimtaion(AnimationWalkingDirections[myAnimationDirection]);
		}

	}
	else
	{
		StopAnimation();
	}

	height = GetPosition().y;
	scale = myScaleConstant + height * myScaleSlope;
	SetSize(Vector2f(scale, scale));

}
void Player::PathFinding()
{
	
	float x1 = myWayPoints[0].x;
	float y1 = myWayPoints[0].y;
	float x2 = myGotoPosition.x;
	float y2 = myGotoPosition.y;
	float x3;
	float y3;
	float x4;
	float y4;
	for (unsigned short i = 0; i < myBordersToCheck.Size(); i++)
	{
		x3 = myBordersToCheck[i].GetNode1().x;
		y3 = myBordersToCheck[i].GetNode1().y;
		x4 = myBordersToCheck[i].GetNode2().x;
		y4 = myBordersToCheck[i].GetNode2().y;

		float d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
		//point where line cross path
		float xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
		float yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

		//Check if path to GotoPosition cross a border.
		if ((xi >= x3 - 0.01f && xi < x4 + 0.01f) && yi >= y3 + 0.01f && yi <= y4 - 0.01f)
		{
			

		}
	}

}
void Player::FindPath(const float aDeltaTime)
{
	(aDeltaTime);
	myVelocity = (myGotoPosition - GetPosition()).Normalize() * mySpeed;
}

float Player::GetDistance(Vector2f aPosition1, Vector2f aPosition2)
{
	return sqrt((aPosition2.x - aPosition1.x)*(aPosition2.x - aPosition1.x) + (aPosition2.y - aPosition1.y)*(aPosition2.y - aPosition1.y));
}

bool Player::BorderIntersect(const Border &aBorder, const Vector2f &aStartPoint, const Vector2f &anEndPoint, Vector2f &anIntersectionPoint)
{
	return Intersection2D::LineVsLine(Intersection2D::LineSegment2D(aStartPoint, anEndPoint), Intersection2D::LineSegment2D(aBorder.GetNode1(), aBorder.GetNode2()), anIntersectionPoint);
}

Player::~Player()
{
}
