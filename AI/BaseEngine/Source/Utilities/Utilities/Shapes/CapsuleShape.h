#pragma once

namespace SB
{

	struct CapsuleShape
	{
		CapsuleShape(const Vector3f & aFirstPosition, const float aLength, const float aRadius) : myCenterPosition(aFirstPosition), myLength(aLength), myRadius(aRadius)
		{}
		CapsuleShape() : myCenterPosition(Vector3f::One), myRadius(1.f), myLength(3.f)
		{}

		Vector3f myCenterPosition;
		float myLength;
		float myRadius;
	};

}