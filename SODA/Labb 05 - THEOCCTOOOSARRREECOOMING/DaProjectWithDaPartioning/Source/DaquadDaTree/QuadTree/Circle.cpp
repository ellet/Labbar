#include "stdafx.h"
#include "Circle.h"
#include <Rend/StaticSprite.h>
#include "QuadTree/PointOfView.h"



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

void Circle::Init(const CU::Vector3f & aPosition, const float aRadius)
{
	Randomizer randoooom;

	mySphere.myCenterPosition = aPosition;
	mySphere.myRadius = aRadius;
	mySphere.myRadiusSquared = aRadius * aRadius;

	//myColor = CU::Vector4f(aPosition.x / 800.f, aPosition.y / 800.f, aPosition.z / 800.f, 0.25f);
	myColor = CU::Vector4f::One;

	mySprite->Init("Sprites/DaObjectsCircle.dds");
	mySprite->SetColor(myColor);
	mySprite->SetLayer(enumRenderLayer::eCircle);
	mySprite->SetSize( /*1.f -*/ (mySphere.myRadius / 24.f));
}

void Circle::Draw() const
{	
	mySprite->Draw(CU::Vector2f(mySphere.myCenterPosition.x, mySphere.myCenterPosition.y));
}

void Circle::Reset()
{
	myIsSeen = false;
	myColor.a = 0.25f;
	mySprite->SetColor(myColor);
}

void Circle::SetIsSeen()
{
	myIsSeen = true;
	myColor.a = 1.f;
	mySprite->SetColor(myColor);
}

bool Circle::CollisionTest(const PointOfView & aPointOfView)
{
	if (Intersection3D::SphereVsFrustum( mySphere, aPointOfView.GetFrustum()) == true)
	{
		return true;
	}
	return false;
}


float Circle::GetRadius() const
{
	return mySphere.myRadius;
}

void Circle::SetParentNode(OctoNode * aParentNode)
{
	myParentNode = aParentNode;
}

OctoNode * Circle::GetParentNode() const
{
	return myParentNode;
}

void Circle::Update(const CU::Time & aTime)
{
	Reset();

}
