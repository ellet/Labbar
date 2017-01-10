#pragma once
#include "Utilities/Randomizer/Randomizer.h"

namespace SB
{

	class RandomDistributionShape
	{
	public:
		RandomDistributionShape();
		virtual ~RandomDistributionShape();

		virtual Vector3f GetRandomPoint() = 0;

	protected:
		Randomizer myRandomizer;
	};
}