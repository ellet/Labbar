#pragma once

namespace ENGINE_NAMESPACE
{

	struct CapsuleShape
	{
		CapsuleShape(const Vector3f & aFirstPosition, const Vector3f & aLengthAndDirection, const float aRadius) : myFirstPosition(aFirstPosition), myLengthAndDirection(aLengthAndDirection), myRadius(aRadius)
		{}
		CapsuleShape() : myFirstPosition(Vector3f::One), myRadius(1.f)
		{}

		Vector3f myFirstPosition;
		Vector3f myLengthAndDirection;
		float myRadius;
	};

}