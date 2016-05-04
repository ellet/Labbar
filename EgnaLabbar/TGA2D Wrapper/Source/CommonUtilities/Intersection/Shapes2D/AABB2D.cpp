#include "AABB2D.h"

namespace Intersection2D
{

	AABB2D::AABB2D()
	{
		myMainPoint = Vector2f::Zero;
		myExtents = Vector2f::Half;
		myMinPos = -Vector2f::Half;
		myMaxPos = Vector2f::Half;;
	}

	AABB2D::AABB2D(const Vector2f aCenterPosition, Vector2f aExtents)
	{
		SetPositionAndSize(aCenterPosition, aExtents);
	}

	void AABB2D::ChangePosition(const Vector2f aPosition)
	{
		myMainPoint = aPosition;
		CalculateMinMax();
	}

	AABB2D::~AABB2D()
	{
	}

}