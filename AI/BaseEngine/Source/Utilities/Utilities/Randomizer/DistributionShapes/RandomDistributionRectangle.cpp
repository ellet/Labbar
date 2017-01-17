#include "stdafx.h"
#include "RandomDistributionRectangle.h"

namespace SB
{

	RandomDistributionRectangle::RandomDistributionRectangle(const Vector3f & someExtents)
	{
		myExtents.x = abs(someExtents.x);
		myExtents.y = abs(someExtents.y);
		myExtents.z = abs(someExtents.z);
	}

	RandomDistributionRectangle::~RandomDistributionRectangle()
	{
	}

	Vector3f RandomDistributionRectangle::GetRandomPoint()
	{
		Vector3f point;

		point.x = myRandomizer.GetRandomValue(-myExtents.x, myExtents.x);
		point.y = myRandomizer.GetRandomValue(-myExtents.y, myExtents.y);
		point.z = myRandomizer.GetRandomValue(-myExtents.z, myExtents.z);

		return point;
	}

}