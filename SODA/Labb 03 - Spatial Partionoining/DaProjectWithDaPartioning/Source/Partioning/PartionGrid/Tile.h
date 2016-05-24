#pragma once
#include "Circle.h"
#include <CU/Intersection/Intersection2D.h>

class Tile
{
public:
	Tile()
	{
	}

	void Init()
	{
		mySquare.SetPositionAndSize(CU::Vector2f(0.f, 0.f), CU::Vector2f(20.f, 20.f));
		myObjectOnTop = nullptr;
		mySprite = new StaticSprite();
		mySprite->Init("Sprites/square.dds");
	}

	Circle * GetObjectOnTop() const
	{
		return myObjectOnTop;
	}

	void SetObjectOnTop(Circle * aCircle)
	{
		myObjectOnTop = aCircle;
	}

	void SetPosition(const CU::Vector2f & aPosition)
	{
		mySquare.ChangePosition(aPosition + mySquare.myExtents);
	}

	void Draw() const
	{
		mySprite->Draw(mySquare.myMainPoint);
	}

	void SetToSeen()
	{
		mySprite->SetColor(CU::Vector4f::One);
	}

	void Reset()
	{
		mySprite->SetColor(CU::Vector4f(1.f, 1.f, 1.f, 0.25f));
	}

	bool CollisionTest(const PointOfView & aPoV) const
	{
		if (Intersection2D::AABBvsCircle(mySquare, aPoV.GetCircle()) == true)
		{
			return true;
		}
		return false;
	}

	bool CollisionTestRay(const Intersection2D::LineSegment2D & aRay)
	{
		return (myObjectOnTop != nullptr && myObjectOnTop->CollisionTestRay(aRay));
	}

private:
	Circle* myObjectOnTop;
	Intersection2D::AABB2D mySquare;
	StaticSprite * mySprite;
};