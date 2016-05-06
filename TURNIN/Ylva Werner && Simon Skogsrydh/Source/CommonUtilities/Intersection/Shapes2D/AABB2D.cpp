#include "AABB2D.h"
#include "../../Macros/Macros.h"

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

	Vector2f AABB2D::GetClosestPoint(const Vector2f & aPointToCompareTo) const
	{
		Vector2f temp;
		temp.x = MAX(myMinPos.x, MIN(myMaxPos.x, aPointToCompareTo.x));
		temp.y = MAX(myMinPos.y, MIN(myMaxPos.y, aPointToCompareTo.y));

		return temp;
	}

	AABB2D::~AABB2D()
	{
	}

}