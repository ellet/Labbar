#pragma once
#include "BaseShape2D.h"

namespace Intersection2D
{

	class Circle2D : public BaseShape2D
	{
	public:
		Circle2D();
		Circle2D(const Vector2f aPosition, const float aRadius);
		~Circle2D();



		float RadiusSquared() const;

		float myRadius;

	};

}