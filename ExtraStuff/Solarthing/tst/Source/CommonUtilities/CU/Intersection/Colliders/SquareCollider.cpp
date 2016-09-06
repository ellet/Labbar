#include "stdafx.h"
#include "SquareCollider.h"

namespace Intersection2D
{

	SquareCollider::SquareCollider()
	{
	}


	SquareCollider::~SquareCollider()
	{
	}

	bool SquareCollider::CheckCollision(const BaseCollider & aColliderToCheckWith) const
	{
		return aColliderToCheckWith.CheckCollisionAgainstSquare(*this);
	}

	bool SquareCollider::CheckCollisionAgainstSquare(const SquareCollider & aSquareCollider) const
	{
		return AABBVsAABB2D(*this, aSquareCollider);
	}

	bool SquareCollider::CheckCollisionAgainstCircle(const CircleCollider & aCircleCollider) const
	{
		return AABBvsCircle(*this, aCircleCollider);
	}

}