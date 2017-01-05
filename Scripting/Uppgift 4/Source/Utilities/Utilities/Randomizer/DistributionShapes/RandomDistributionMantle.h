#pragma once
#include "RandomDistributionShape.h"

namespace SB
{

	class RandomDistributionMantle : public RandomDistributionShape
	{
	public:
		RandomDistributionMantle(const Vector3f & aPosition, const float aRadius, const float aInnerRadiusInPercent);
		RandomDistributionMantle(const SphereShape & aSphere, const float aInnerRadiusInPercent);
		~RandomDistributionMantle();

		virtual Vector3f GetRandomPoint() override;

	private:
		SphereShape mySphere;
		float myInnerRadiusInPercent;
	};

}