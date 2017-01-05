#pragma once

namespace SB
{

	struct BoxShape
	{
		BoxShape(const Vector3f & aPosition, const Vector3f & aExtents) : myPosition(aPosition), myExtents(aExtents)
		{}
		BoxShape() : myPosition(Vector3f::Zero), myExtents(Vector3f::One)
		{}

		Vector3f myPosition;
		Vector3f myExtents;
	};

}