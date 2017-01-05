#pragma once


namespace SB
{

	struct CircleShape
	{
		CircleShape(const Vector2f & aPosition, const float aRadius) : myPosition(aPosition), myRadius(aRadius)
		{}

		Vector2f myPosition;
		float myRadius;

	};
}