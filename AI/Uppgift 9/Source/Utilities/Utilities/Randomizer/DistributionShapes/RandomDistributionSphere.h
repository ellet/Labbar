#pragma once
#include "RandomDistributionShape.h"

namespace SB
{

	class RandomDistributionSphere : public RandomDistributionShape
	{
	public:
		RandomDistributionSphere(const Vector3f & aPosition, const float aRadius);
		RandomDistributionSphere(const SphereShape & aSphere);
		~RandomDistributionSphere();

		virtual Vector3f GetRandomPoint() override;

	private:
		SphereShape mySphere;

	};

}