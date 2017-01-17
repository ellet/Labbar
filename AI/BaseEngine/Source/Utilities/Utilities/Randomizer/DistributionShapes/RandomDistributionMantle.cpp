#include "stdafx.h"
#include "RandomDistributionMantle.h"

namespace SB
{

	RandomDistributionMantle::RandomDistributionMantle(const Vector3f & aPosition, const float aRadius, const float aInnerRadiusInPercent)
	{
		mySphere.myPosition = aPosition;
		mySphere.myRadius = aRadius;
	}

	RandomDistributionMantle::RandomDistributionMantle(const SphereShape & aSphere, const float aInnerRadiusInPercent)
	{
		mySphere = aSphere;
	}

	RandomDistributionMantle::~RandomDistributionMantle()
	{
	}

	Vector3f RandomDistributionMantle::GetRandomPoint()
	{
		Vector3f randomizedPoint;
		float innerRadius = mySphere.myRadius * myInnerRadiusInPercent;
		if (innerRadius >= mySphere.myRadius)
		{
			Error("Random Distribution Shape Error - Mantle - Inner radius must be below 100%, set it to a value below 1!");
		}

		do {
			randomizedPoint.x = myRandomizer.GetRandomValue(-mySphere.myRadius, mySphere.myRadius);
			randomizedPoint.y = myRandomizer.GetRandomValue(-mySphere.myRadius, mySphere.myRadius);
			randomizedPoint.z = myRandomizer.GetRandomValue(-mySphere.myRadius, mySphere.myRadius);
		} while ((randomizedPoint.x * randomizedPoint.x + randomizedPoint.y * randomizedPoint.y + randomizedPoint.z * randomizedPoint.z) > (mySphere.myRadius * mySphere.myRadius) &&
			(randomizedPoint.x * randomizedPoint.x + randomizedPoint.y * randomizedPoint.y + randomizedPoint.z * randomizedPoint.z) < (innerRadius * innerRadius));

		return randomizedPoint + mySphere.myPosition;
	}

}