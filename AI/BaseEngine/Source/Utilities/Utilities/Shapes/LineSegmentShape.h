#pragma once
#include "Utilities\Math\Vector3.h"

namespace SB
{

	struct LineSegmentShape
	{
		LineSegmentShape(const Vector3f & aFirstPosition, const Vector3f & aSecondPosition) : myFirstPosition(aFirstPosition), mySecondPosition(aSecondPosition)
		{}
		LineSegmentShape() : myFirstPosition(Vector3f::Zero), mySecondPosition(Vector3f::UnitZ)
		{}

		Vector3f myFirstPosition;
		Vector3f mySecondPosition;
	};	

}

