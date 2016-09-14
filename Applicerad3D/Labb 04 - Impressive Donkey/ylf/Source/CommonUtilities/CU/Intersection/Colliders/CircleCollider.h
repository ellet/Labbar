#pragma once
#include "CU/Intersection/Colliders/BaseCollider.h"
#include "CU/Intersection/Shapes2D/Circle2D.h"


namespace Intersection2D
{

	class CircleCollider : public BaseCollider, public Circle2D
	{
	public:
		CircleCollider();
		~CircleCollider();

		CircleCollider(const CU::Vector2f aPosition, const float aRadius) : Circle2D(aPosition, aRadius)
		{}

		virtual bool CheckCollision(const BaseCollider & aColliderToCheckWith) const override;

		virtual bool CheckCollisionAgainstSquare(const SquareCollider & aSquareCollider) const override;
		virtual bool CheckCollisionAgainstCircle(const CircleCollider & aCircleCollider) const override;
	};
}