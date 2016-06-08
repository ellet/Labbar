#include "stdafx.h"
#include "Circle.h"
#include <Rend/StaticSprite.h>
#include "KDtree/PointOfView.h"



CU::Vector2f Circle::ourConstraints = CU::Vector2f(800.f, 800.f);
Randomizer Circle::ourRandomizer;

const CU::Vector4f SeenColor = CU::Vector4f(1.f, 1.f, 1.f, 0.7f);
const CU::Vector4f ShadowColor = CU::Vector4f(1.f, 0.f, 0.f, 0.2f);
const CU::Vector4f CheckedColor = CU::Vector4f(1.f, 0.5f, 0.5f, 0.4f);

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

void Circle::Init(const CU::Vector2f & aPosition, const float aRadius)
{
	Randomizer randoooom;

	myCircle.myMainPoint = aPosition;
	myCircle.myRadius = aRadius;

	//myColor = CU::Vector4f(aPosition.x / 800.f, aPosition.y / 800.f, aPosition.z / 800.f, 0.25f);
	myColor = ShadowColor;

	mySprite->Init("Sprites/DaObjectsCircle.dds");
	mySprite->SetColor(myColor);
	mySprite->SetLayer(enumRenderLayer::eCircle);
	mySprite->SetSize( /*1.f -*/ (myCircle.myRadius / 24.f));
}

void Circle::Draw() const
{	
	mySprite->Draw(CU::Vector2f(myCircle.myMainPoint.x, myCircle.myMainPoint.y));
}

void Circle::Reset()
{
	myIsSeen = false;
	myColor.a = 0.25f;
	mySprite->SetColor(ShadowColor);
}

void Circle::SetIsSeen()
{
	myIsSeen = true;
	myColor.a = 1.f;
	mySprite->SetColor(SeenColor);
}

void Circle::SetLayerChecked()
{
	myColor.a = 1.f;
	mySprite->SetColor(CheckedColor);
}

bool Circle::CollisionTest(const PointOfView & aPointOfView)
{
	/*if (Intersection3D::SphereVsFrustum( my, aPointOfView.GetFrustum()) == true)
	{
		return true;
	}*/
	return false;
}


float Circle::GetRadius() const
{
	return myCircle.myRadius;
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
