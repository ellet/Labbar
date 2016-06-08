#pragma once
#include "BaseShape.h"
#include "CU/Lines And Planes/plane.h"

namespace Intersection3D
{


	class Fov90Frustum : public BaseShape
	{
	public:
		Fov90Frustum(const CU::Vector3f & aPosition, float aNearPlaneDistance, float aFarPlaneDistance, const CU::Vector3f & aDirection);

		const CU::Vector3f & Fov90Frustum::GetDirection() const;

		const CU::Point3f Fov90Frustum::GetNearTopLeft() const;

		const CU::Point3f Fov90Frustum::GetNearTopRight() const;

		const CU::Point3f Fov90Frustum::GetNearDownLeft() const;

		const CU::Point3f Fov90Frustum::GetNearDownRight() const;

		const CU::Point3f Fov90Frustum::GetFarTopLeft() const;

		const CU::Point3f Fov90Frustum::GetFarTopRight() const;

		const CU::Point3f Fov90Frustum::GetFarDownLeft() const;

		const CU::Point3f Fov90Frustum::GetFarDownRight() const;



		float myNearPlaneDistance;
		float myFarPlaneDistance;

		Plane<float> myNearPlane;
		Plane<float> myRightPlane;
		Plane<float> myTopPlane;
		Plane<float> myLeftPlane;
		Plane<float> myDownPlane;
		Plane<float> myFarPlane;
	};
}