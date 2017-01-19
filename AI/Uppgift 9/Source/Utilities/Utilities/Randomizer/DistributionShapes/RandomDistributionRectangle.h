#pragma once
#include "RandomDistributionShape.h"

namespace SB
{
	class RandomDistributionRectangle : public RandomDistributionShape
	{
	public:
		RandomDistributionRectangle(const Vector3f & someExtents);
		~RandomDistributionRectangle();

		virtual Vector3f GetRandomPoint() override;

	private:
		Vector3f myExtents;
	};

}