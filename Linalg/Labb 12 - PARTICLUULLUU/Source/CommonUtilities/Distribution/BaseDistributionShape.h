#pragma once
#include "../Vectors/vector3.h"
#include "../Utility/Randomizer/Randomizer.h"

class BaseDistributionShape
{
public:
	BaseDistributionShape();
	virtual ~BaseDistributionShape();

	virtual Vector3f GetPositionInDistribution() = 0;

protected:
	Randomizer myRandomizer;
};