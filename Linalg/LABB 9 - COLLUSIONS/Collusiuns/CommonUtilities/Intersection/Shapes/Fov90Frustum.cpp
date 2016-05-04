#include "Fov90Frustum.h"
#include "../../Macros/Macros.h"
#include <math.h>

namespace Intersection
{


	Fov90Frustum::Fov90Frustum(float aNearPlaneDistance, float aFarPlaneDistance)
	{
		myNearPlaneDistance = aNearPlaneDistance;
		myFarPlaneDistance = aFarPlaneDistance;

		float rotate45 = sin(DEGRESS_TO_RADIANS(45));
		float nearX = (tan(DEGRESS_TO_RADIANS(45) / aNearPlaneDistance));
		float nearY = (tan(DEGRESS_TO_RADIANS(45) / aNearPlaneDistance));

		float farX = (tan(DEGRESS_TO_RADIANS(45) / aFarPlaneDistance));
		float farY = (tan(DEGRESS_TO_RADIANS(45) / aFarPlaneDistance));


		myNearPlane	= Plane<float>(Vector3f(0.f, 0.f, aNearPlaneDistance), Vector3f(0.f, 0.f, -1.f));
		myRightPlane = Plane<float>(Vector3f::Zero, Vector3f(rotate45, 0.f, -rotate45));
		myTopPlane = Plane<float>(Vector3f::Zero, Vector3f(0.f, rotate45, -rotate45));
		myLeftPlane = Plane<float>(Vector3f::Zero, Vector3f(-rotate45, 0.f, -rotate45));
		myDownPlane = Plane<float>(Vector3f::Zero, Vector3f(0.f, -rotate45, -rotate45));
		myFarPlane = Plane<float>(Vector3f(0.f, 0.f, aFarPlaneDistance), Vector3f(0.f, 0.f, 1.f));
	}

};