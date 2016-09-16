#pragma once
#include "CU/Intersection/Colliders/BaseCollider.h"
#include "CU/Intersection/Shapes2D/AABB2D.h"

namespace Intersection2D
{

	class SquareCollider : public BaseCollider,  public AABB2D
	{
	public:
		SquareCollider();
		~SquareCollider();

		SquareCollider(const CU::Vector2f aCenterPosition, const CU::Vector2f aExtents) : AABB2D(aCenterPosition, aExtents)
		{}

		virtual bool CheckCollision(const BaseCollider & aColliderToCheckWith) const override;

		
		virtual bool CheckCollisionAgainstSquare(const SquareCollider & aSquareCollider) const override;

		virtual bool CheckCollisionAgainstCircle(const CircleCollider & aCircleCollider) const override;

	};

}