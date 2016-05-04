#include "SphereDistribution.h"
#include "../../Matriser/matrix33.h"


SphereDistribution::SphereDistribution()
{
}


SphereDistribution::~SphereDistribution()
{
}

void SphereDistribution::SetSphere(Vector3f aPosition, const float aRadius, const float aDistancePercentage)
{
	mySphere.myCenterPosition = aPosition;
	mySphere.myRadius = aRadius;
	mySphere.myRadiusSquared = aRadius * aRadius;

	myDistanceFromCenterPercentage = aDistancePercentage;
}

Vector3f SphereDistribution::GetPositionInDistribution()
{
	const float X = myRandomizer.GetRandomValue(myDistanceFromCenterPercentage * mySphere.myRadius, mySphere.myRadius);
	const float Y = myRandomizer.GetRandomValue(myDistanceFromCenterPercentage * mySphere.myRadius, mySphere.myRadius);
	const float Z = myRandomizer.GetRandomValue(myDistanceFromCenterPercentage * mySphere.myRadius, mySphere.myRadius);

	Vector3f tempVector = Vector3f(X, Y, Z);
	tempVector = tempVector * Matrix33f::CreateRotateAroundX(DEGRESS_TO_RADIANSF(myRandomizer.GetRandomValue(0.f, 359.f)));
	tempVector = tempVector * Matrix33f::CreateRotateAroundY(DEGRESS_TO_RADIANSF(myRandomizer.GetRandomValue(0.f, 359.f)));
	tempVector = tempVector * Matrix33f::CreateRotateAroundZ(DEGRESS_TO_RADIANSF(myRandomizer.GetRandomValue(0.f, 359.f)));

	tempVector += mySphere.myCenterPosition;

	return tempVector;
}
