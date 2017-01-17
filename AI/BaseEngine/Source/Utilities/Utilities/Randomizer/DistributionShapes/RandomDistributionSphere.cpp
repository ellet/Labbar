#include "stdafx.h"
#include "RandomDistributionSphere.h"

namespace SB
{

	RandomDistributionSphere::RandomDistributionSphere(const Vector3f & aPosition, const float aRadius)
	{
		mySphere.myPosition = aPosition;
		mySphere.myRadius = aRadius;
	}

	RandomDistributionSphere::RandomDistributionSphere(const SphereShape & aSphere)
	{
		mySphere = aSphere;
	}

	RandomDistributionSphere::~RandomDistributionSphere()
	{
	}

	Vector3f RandomDistributionSphere::GetRandomPoint()
	{
		Vector3f randomizedPoint;

		do {
			randomizedPoint.x = myRandomizer.GetRandomValue(-mySphere.myRadius, mySphere.myRadius);
			randomizedPoint.y = myRandomizer.GetRandomValue(-mySphere.myRadius, mySphere.myRadius);
			randomizedPoint.z = myRandomizer.GetRandomValue(-mySphere.myRadius, mySphere.myRadius);
		} while ((randomizedPoint.x * randomizedPoint.x + randomizedPoint.y * randomizedPoint.y + randomizedPoint.z * randomizedPoint.z) > (mySphere.myRadius * mySphere.myRadius));

		return randomizedPoint + mySphere.myPosition;
	}

}