#include "stdafx.h"
#include "CircleCollider.h"
#include "..\Intersection2D.h"

namespace Intersection2D
{

	CircleCollider::CircleCollider()
	{
	}


	CircleCollider::~CircleCollider()
	{
	}

	bool CircleCollider::CheckCollision(const BaseCollider & aColliderToCheckWith) const
	{
		return aColliderToCheckWith.CheckCollisionAgainstCircle(*this);
	}

	bool CircleCollider::CheckCollisionAgainstSquare(const SquareCollider & aSquareCollider) const
	{
		return AABBvsCircle(aSquareCollider, *this);
	}


	bool CircleCollider::CheckCollisionAgainstCircle(const CircleCollider & aCircleCollider) const
	{
		return CircleVSCircle(*this, aCircleCollider);
	}

}