#include "stdafx.h"
#include "Fov90Frustum.h"
#include "CU/Macros/Macros.h"
#include <math.h>
#include <CU/Matriser/matrix44.h>

namespace Intersection3D
{
	Fov90Frustum::Fov90Frustum(const CU::Vector3f & aPosition ,float aNearPlaneDistance, float aFarPlaneDistance, const CU::Vector3f & aDirection)
	{
		CU::Matrix44f translation = CU::Matrix44f::Identity;
		translation *= translation.CreateRotateAroundX((DEGRESS_TO_RADIANSF(aDirection.x)));
		translation *= translation.CreateRotateAroundY((DEGRESS_TO_RADIANSF(aDirection.y)));
		translation *= translation.CreateRotateAroundZ((DEGRESS_TO_RADIANSF(aDirection.z)));

		myNearPlaneDistance = aNearPlaneDistance;
		myFarPlaneDistance = aFarPlaneDistance;

		float rotate45 = static_cast<float>(sin(DEGRESS_TO_RADIANSF(45)));

		myNearPlane = Plane<float>(((CU::Vector3f(0.f, 0.f, aNearPlaneDistance) * translation) + aPosition ),
			(CU::Vector3f(0.f, 0.f, -1.f) * translation));

		myRightPlane = Plane<float>(aPosition,
			(CU::Vector3f(rotate45, 0.f, -rotate45) * translation));

		myTopPlane = Plane<float>(aPosition,
			(CU::Vector3f(0.f, rotate45, -rotate45) * translation));

		myLeftPlane = Plane<float>(aPosition,
			(CU::Vector3f(-rotate45, 0.f, -rotate45) * translation) );

		myDownPlane = Plane<float>(aPosition,
			(CU::Vector3f(0.f, -rotate45, -rotate45) * translation) );

		myFarPlane = Plane<float>(((CU::Vector3f(0.f, 0.f, aFarPlaneDistance) * translation) + aPosition),
			(CU::Vector3f(0.f, 0.f, 1.f) * translation));
	}

	const CU::Vector3f & Fov90Frustum::GetDirection() const
	{
		return myNearPlane.GetNormal();
	}

	const CU::Point3f Fov90Frustum::GetNearTopLeft() const
	{
		CU::Point3f corner = CU::Vector3f::Zero;
		IntersectionPoint3Planes(myNearPlane, myLeftPlane, myTopPlane, corner);
		return corner;
	}

	const CU::Point3f Fov90Frustum::GetNearTopRight() const
	{
		CU::Point3f corner = CU::Vector3f::Zero;
		IntersectionPoint3Planes(myNearPlane, myRightPlane, myTopPlane, corner);
		return corner;
	}

	const CU::Point3f Fov90Frustum::GetNearDownLeft() const
	{
		CU::Point3f corner = CU::Vector3f::Zero;
		IntersectionPoint3Planes(myNearPlane, myLeftPlane, myDownPlane, corner);
		return corner;
	}

	const CU::Point3f Fov90Frustum::GetNearDownRight() const
	{
		CU::Point3f corner = CU::Vector3f::Zero;
		IntersectionPoint3Planes(myNearPlane, myRightPlane, myDownPlane, corner);
		return corner;
	}

	const CU::Point3f Fov90Frustum::GetFarTopLeft() const
	{
		CU::Point3f corner = CU::Vector3f::Zero;
		IntersectionPoint3Planes(myFarPlane, myLeftPlane, myTopPlane, corner);
		return corner;
	}

	const CU::Point3f Fov90Frustum::GetFarTopRight() const
	{
		CU::Point3f corner = CU::Vector3f::Zero;
		IntersectionPoint3Planes(myFarPlane, myRightPlane, myTopPlane, corner);
		return corner;
	}

	const CU::Point3f Fov90Frustum::GetFarDownLeft() const
	{
		CU::Point3f corner = CU::Vector3f::Zero;
		IntersectionPoint3Planes(myFarPlane, myLeftPlane, myDownPlane, corner);
		return corner;
	}

	const CU::Point3f Fov90Frustum::GetFarDownRight() const
	{
		CU::Point3f corner = CU::Vector3f::Zero;
		IntersectionPoint3Planes(myFarPlane, myRightPlane, myDownPlane, corner);
		return corner;
	}

};