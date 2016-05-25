#include "stdafx.h"
#include "Circle.h"
#include <Rend/StaticSprite.h>
#include "QuadTree/PointOfView.h"
#include <CU/Intersection/Intersection2D.h>



CU::Vector2f Circle::ourConstraints = CU::Vector2f(800.f, 800.f);
Randomizer Circle::ourRandomizer;

const CU::Vector4f SeenColor = CU::Vector4f(1.f, 1.f, 1.f, 0.7f);
const CU::Vector4f ShadowColor = CU::Vector4f(1.f, 0.f, 0.f, 0.2f);

const float BallSpeed = 10.f;

Circle::Circle()
{
	mySprite = new StaticSprite();
	myIsSeen = false;
}


Circle::~Circle()
{
	SAFE_DELETE(mySprite);
}

void Circle::Init(const CU::Vector2f & aPosition)
{
	myCircle.ChangePosition(aPosition);
	myCircle.myRadius = 24.f;

	myDirection.x = ourRandomizer.GetRandomValue(-1.f, 1.f);
	myDirection.y = ourRandomizer.GetRandomValue(-1.f, 1.f);

	mySprite->Init("sprites/DaObjectsCircle.dds");
	mySprite->SetColor(SeenColor);
	mySprite->SetLayer(enumRenderLayer::eCircle);
}

void Circle::Draw() const
{	
	mySprite->Draw(myCircle.myMainPoint);
}

void Circle::Reset()
{
	myIsSeen = false;
	mySprite->SetColor(ShadowColor);
}

void Circle::SetIsSeen()
{
	myIsSeen = true;
	mySprite->SetColor(SeenColor);
}

bool Circle::CollisionTest(const PointOfView & aPointOfView)
{
	if (Intersection2D::CircleVSCircle(aPointOfView.GetCircle(), myCircle) == true)
	{
		CU::Vector2f tempVector = (myCircle.myMainPoint - aPointOfView.GetPosition());

		float angle;
		if (aPointOfView.GetRotation() > DEGRESS_TO_RADIANSF(360 - 45.f) && tempVector.GetAngle() < DEGRESS_TO_RADIANSF(180.f))
		{
			angle = (tempVector.GetAngle() + DEGRESS_TO_RADIANSF(360.f) - aPointOfView.GetRotation());
		}
		else if (aPointOfView.GetRotation() < DEGRESS_TO_RADIANSF(45.f) && tempVector.GetAngle() > DEGRESS_TO_RADIANSF(180.f))
		{
			angle = (tempVector.GetAngle() - DEGRESS_TO_RADIANSF(360.f) - aPointOfView.GetRotation());
		}
		else
		{
			angle = (tempVector.GetAngle() - aPointOfView.GetRotation());
		}

		if (angle < DEGRESS_TO_RADIANSF(45.f) && angle > DEGRESS_TO_RADIANSF(-45.f))
		{
			return true;
		}
	}
	
	return false;
}

bool Circle::CollisionTestRay(const Intersection2D::LineSegment2D & aRay)
{
	CU::Vector2f meh = CU::Vector2f::One;
	return (Intersection2D::LineVsCircle(aRay, myCircle, meh));
}

float Circle::GetRadius() const
{
	return myCircle.myRadius;
}

void Circle::SetParentNode(QuadNode * aParentNode)
{
	myParentNode = aParentNode;
}

QuadNode * Circle::GetParentNode() const
{
	return myParentNode;
}

void Circle::Update(const CU::Time & aTime)
{
	Reset();
	MoveBall(myDirection * aTime.GetSeconds() * BallSpeed);
}

void Circle::MoveBall(const CU::Vector2f & aDelta)
{
	CU::Vector2f newPosition = aDelta + myCircle.myMainPoint;
	if (newPosition.x > (ourConstraints.x - myCircle.myRadius) || newPosition.x < myCircle.myRadius)
	{
		myDirection.x = -myDirection.x;
		newPosition.x = myCircle.myMainPoint.x;
	}

	if (newPosition.y > (ourConstraints.y - myCircle.myRadius) || newPosition.y < myCircle.myRadius)
	{
		myDirection.y = -myDirection.y;
		newPosition.y = myCircle.myMainPoint.y;
	}

	myCircle.ChangePosition(newPosition);
}