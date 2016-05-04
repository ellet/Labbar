#pragma once

#include "../BaseDistributionShape.h"
#include "../../Intersection/Shapes/AABB.h"

class BoxDistibution : public BaseDistributionShape
{
public:
	BoxDistibution();
	~BoxDistibution();

	void SetBox(const Vector3f aPosition, const Vector3f aExtents);
	void SetBoxWithMinMax(const Vector3f aMinValue, const Vector3f aMaxValue);

	virtual Vector3f GetPositionInDistribution() override;

private:
	Intersection3D::AABB myBoxShape;
};

