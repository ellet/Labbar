#pragma once
#include "../../Intersection/Shapes/Sphere.h"

#include "../BaseDistributionShape.h"

class SphereDistribution : public BaseDistributionShape
{
public:
	SphereDistribution();
	~SphereDistribution();

	void SetSphere(Vector3f aPosition, const float aRadius, const float aDistancePercentage);

	virtual Vector3f GetPositionInDistribution() override;

private:
	Intersection3D::Sphere mySphere;
	float myDistanceFromCenterPercentage;
};

