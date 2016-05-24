#include "stdafx.h"
#include "Circle.h"
#include <Rend/StaticSprite.h>
#include "PartionGrid/PointOfView.h"
#include <CU/Intersection/Intersection2D.h>

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

	mySprite->Init("sprites/DaObjectsCircle.dds");
	mySprite->SetLayer(enumRenderLayer::eCircle);
}

void Circle::Draw() const
{	
	mySprite->Draw(myCircle.myMainPoint);
}

void Circle::Reset()
{
	myIsSeen = false;
	mySprite->SetColor(CU::Vector4f(1.f, 0.f, 0.f, 0.2f));
}

void Circle::SetIsSeen()
{
	myIsSeen = true;
	mySprite->SetColor(CU::Vector4f::One);
}

bool Circle::CollisionTest(const PointOfView & aPointOfView)
{
	return (Intersection2D::CircleVSCircle(aPointOfView.GetCircle(), myCircle));
}

bool Circle::CollisionTestRay(const Intersection2D::LineSegment2D & aRay)
{
	CU::Vector2f meh = CU::Vector2f::One;
	return (Intersection2D::LineVsCircle(aRay, myCircle, meh));
}

void Circle::Update()
{
	Reset();
}