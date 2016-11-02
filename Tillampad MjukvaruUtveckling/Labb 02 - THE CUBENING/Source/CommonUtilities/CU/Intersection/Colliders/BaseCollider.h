#pragma once


namespace Intersection2D
{
	class SquareCollider;
	class CircleCollider;

	class BaseCollider
	{
	public:
		BaseCollider()
		{}
		virtual ~BaseCollider()
		{}

		virtual bool CheckCollision(const BaseCollider & aColliderToCheckWith) const = 0;
		
		virtual bool CheckCollisionAgainstSquare(const SquareCollider & aSquareCollider) const
		{
			(aSquareCollider);
			return false;
		}

		virtual bool CheckCollisionAgainstCircle(const CircleCollider & aCircleCollider) const
		{
			(aCircleCollider);
			return false;
		}
	};

}