#pragma once
#include "CU/Intersection/Shapes.h"
#include "CU/Intersection/Shapes2D/LineSegment2D.h"
#include <cmath>

namespace Intersection3D
{
	inline float DistanceToLine(const LineSegment3D & aLine, const CU::Vector3f & aPositition)
	{
		CU::Vector3f d = aLine.myEndPos - aLine.myStartPos;
		d.Normalize();

		CU::Vector3f e = (aPositition - aLine.myStartPos);
		CU::Vector3f a = (e * d.Length());

		return (e.Length2() - a.Length2());
	}

	inline bool CompareRadiusOfLineToDistanceOfPoint(const LineSegment3D & aLine, const CU::Vector3f & aPositition, const float aRadius, const float myRadius = 0.f)
	{
		if ((aRadius + myRadius) > DistanceToLine(aLine, aPositition))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool PointInsideSphere(const Sphere & aSphere, const CU::Vector3f & aPoint)
	{
		CU::Vector3f temp;
		temp = aSphere.myCenterPosition - aPoint;

		if (temp.Length() < aSphere.myRadius)
		{
			return true;
		}
		return false;
	}

	inline bool PointInsideAABB(const AABB & aAABB, const CU::Vector3f & aPoint)
	{
		if (aPoint.x > aAABB.myMinPos.x &&
			aPoint.x < aAABB.myMaxPos.x &&
			aPoint.y > aAABB.myMinPos.y &&
			aPoint.y < aAABB.myMaxPos.y &&
			aPoint.z > aAABB.myMinPos.z &&
			aPoint.z < aAABB.myMaxPos.z)
		{
			return true;
		}
		return false;
	}


	// Compute the point p at which the three planes p1, p2 and p3 intersect (if at all)

	inline bool IntersectionPoint3Planes(
		const Plane<float> & p1, 
		const Plane<float> &  p2, 
		const Plane<float> &  p3, 
		CU::Point3f &p)
	{

		CU::Vector3f m1 = CU::Vector3f(p1.GetNormal().x, p2.GetNormal().x, p3.GetNormal().x);

		CU::Vector3f m2 = CU::Vector3f(p1.GetNormal().y, p2.GetNormal().y, p3.GetNormal().y);

		CU::Vector3f m3 = CU::Vector3f(p1.GetNormal().z, p2.GetNormal().z, p3.GetNormal().z);

		CU::Vector3f u = m2.Cross(m3);

		float denom = m1.Dot(u);

		if (abs(denom) < 0.001f) return false; // Planes do not intersect in a point

		CU::Vector3f d(p1.GetDistanceFromOrigin(), p2.GetDistanceFromOrigin(), p3.GetDistanceFromOrigin());

		CU::Vector3f v = m1.Cross(d);

		float ood = 1.0f / denom;

		p.x = d.Dot(u) * ood;

		p.y = m3.Dot(v) * ood;

		p.z = -m2.Dot(v) * ood;

		return true;
	}

	inline bool LineVsSphere(const LineSegment3D & aLine, const Sphere & aSphere, CU::Vector3f & anIntersectionPoint)
	{
		CU::Vector3f hypotenuse = aSphere.myCenterPosition - aLine.myStartPos;

		CU::Vector3f directionOfLine = aLine.myEndPos - aLine.myStartPos;
		directionOfLine.Normalize();

		CU::Vector3f lineToMiddle = (directionOfLine * hypotenuse.Length());
		float toRoot = (aSphere.myRadiusSquared - hypotenuse.Length2() + lineToMiddle.Length2());
		if (toRoot < 0)
		{
			return false;
		}
		float perpendicular = (sqrt(toRoot));
		float difference = lineToMiddle.Length() - perpendicular;
		anIntersectionPoint = aLine.myStartPos + (directionOfLine * difference);
		if ((difference * difference) > (aLine.myEndPos - aLine.myStartPos).Length2())
		{
			return false;
		}

		return true;
	}


	inline bool SweptSphereVsSphere(const LineSegment3D & aLine, float aRadius, Sphere aSphere)
	{
		//float b = DistanceToLine(aLine, aSphere.myCenterPosition);

		aSphere.myRadius += aRadius;
		aSphere.myRadiusSquared = aSphere.myRadius * aSphere.myRadius;

		return LineVsSphere(aLine, aSphere, CU::Vector3f());
	}

	inline bool AABBvsSphere(const AABB & aAABB, const Sphere & aSphere)
	{
		return PointInsideSphere(aSphere,aAABB.GetClosestPoint(aSphere.myCenterPosition));
	}

	inline bool SphereIsInsideAABB(const Sphere & aSphere, const AABB & aAABB)
	{
		if (PointInsideAABB(aAABB, aSphere.myCenterPosition) == true)
		{
			CU::Vector3f offset = aSphere.myCenterPosition - aAABB.myCenterPos;
			if ((aAABB.myExtents.x - aSphere.myRadius) > abs(offset.x) &&
				(aAABB.myExtents.y - aSphere.myRadius) > abs(offset.y) &&
				(aAABB.myExtents.z - aSphere.myRadius) > abs(offset.z))
			{
				return true;
			}
		}
		return false;
	}

	inline bool LineVsAABB(const LineSegment3D & aLine, const AABB & aAABB, CU::Vector3f & anIntersectionPoint)
	{
		bool isInside = true;

		CU::Vector3f rayDelta = aLine.myEndPos - aLine.myStartPos;
		union
		{
			float xt;
			float distanceToXPlane;
		};

		if (aLine.myStartPos.x < aAABB.myMinPos.x)
		{
			distanceToXPlane = aAABB.myMinPos.x - aLine.myStartPos.x;
			if (distanceToXPlane > rayDelta.x)
			{
				return false;
			}
			distanceToXPlane /= rayDelta.x;
			isInside = false;
		}
		else if (aLine.myStartPos.x > aAABB.myMaxPos.x)
		{
			distanceToXPlane = aAABB.myMaxPos.x - aLine.myStartPos.x;
			if (distanceToXPlane < rayDelta.x)
			{
				return false;
			}
			distanceToXPlane /= rayDelta.x;
			isInside = false;
		}
		else
		{
			distanceToXPlane = -1.f;
		}

		union
		{
			float yt;
			float distanceToYPlane;
		};

		if (aLine.myStartPos.y < aAABB.myMinPos.y)
		{
			distanceToYPlane = aAABB.myMinPos.y - aLine.myStartPos.y;
			if (distanceToYPlane > rayDelta.y)
			{
				return false;
			}
			distanceToYPlane /= rayDelta.y;
			isInside = false;
		}
		else if (aLine.myStartPos.y > aAABB.myMaxPos.y)
		{
			distanceToYPlane = aAABB.myMaxPos.y - aLine.myStartPos.y;
			if (distanceToYPlane < rayDelta.y)
			{
				return false;
			}
			distanceToYPlane /= rayDelta.y;
			isInside = false;
		}
		else
		{
			distanceToYPlane = -1.f;
		}

		union
		{
			float zt;
			float distanceToZPlane;
		};

		if (aLine.myStartPos.z < aAABB.myMinPos.z)
		{
			distanceToZPlane = aAABB.myMinPos.z - aLine.myStartPos.z;
			if (distanceToZPlane > rayDelta.z)
			{
				return false;
			}
			distanceToZPlane /= rayDelta.z;
			isInside = false;
		}
		else if (aLine.myStartPos.z > aAABB.myMaxPos.z)
		{
			distanceToZPlane = aAABB.myMaxPos.z - aLine.myStartPos.z;
			if (distanceToZPlane < rayDelta.z)
			{
				return false;
			}
			distanceToZPlane /= rayDelta.z;
			isInside = false;
		}
		else
		{
			distanceToZPlane = -1.f;
		}

		if (isInside == true)
		{
			anIntersectionPoint = aLine.myStartPos;
			return true;
		}

		int hitOnWhichSide = 0;

		union
		{
			float lengthAtIntersectionOfLine;
			float t;
		};

		lengthAtIntersectionOfLine = distanceToXPlane;
		if (distanceToYPlane > lengthAtIntersectionOfLine)
		{
			hitOnWhichSide = 1;
			lengthAtIntersectionOfLine = distanceToYPlane;
		}

		if (distanceToZPlane > lengthAtIntersectionOfLine)
		{
			hitOnWhichSide = 2;
			lengthAtIntersectionOfLine = distanceToZPlane;
		}

		float x = 0;
		float y = 0;
		float z = 0;

		switch (hitOnWhichSide)
		{
		case 0:
			//intersect with yz plane

			y = aLine.myStartPos.y + rayDelta.y * lengthAtIntersectionOfLine;
			if (y < aAABB.myMinPos.y || y > aAABB.myMaxPos.y)
			{
				return false;
			}

			z = aLine.myStartPos.z + rayDelta.z * lengthAtIntersectionOfLine;
			if (z < aAABB.myMinPos.z || z > aAABB.myMaxPos.z)
			{
				return false;
			}

			break;

		case 1:
			//intersect with xz plane

			x = aLine.myStartPos.x + rayDelta.x * lengthAtIntersectionOfLine;
			if (x < aAABB.myMinPos.x || x > aAABB.myMaxPos.x)
			{
				return false;
			}

			z = aLine.myStartPos.z + rayDelta.z * lengthAtIntersectionOfLine;
			if (z < aAABB.myMinPos.z || z > aAABB.myMaxPos.z)
			{
				return false;
			}
			break;

		case 2:
			//intersect with xy plane

			x = aLine.myStartPos.x + rayDelta.x * lengthAtIntersectionOfLine;
			if (x < aAABB.myMinPos.x || x > aAABB.myMaxPos.x)
			{
				return false;
			}

			y = aLine.myStartPos.y + rayDelta.y * lengthAtIntersectionOfLine;
			if (y < aAABB.myMinPos.y || y > aAABB.myMaxPos.y)
			{
				return false;
			}

			break;

		default:
			break;
		}

		anIntersectionPoint = (rayDelta.GetNormalized() * lengthAtIntersectionOfLine);

		return true;
	}
	
	inline bool SweptSphereVsAABB(const LineSegment3D & aLine, float aRadius, AABB aAABB)
	{
		CU::Vector3f distanceToChange = CU::Vector3f::DirectionVector45Deg * aRadius;
		aAABB.myMaxPos += distanceToChange;
		aAABB.myMinPos -= distanceToChange;

		return LineVsAABB(aLine, aAABB, CU::Vector3f());
	}

	inline bool SphereVsPlane(const Sphere & aSphere, const Plane<float> & aPlane)
	{
		if (aSphere.myCenterPosition.Dot(aPlane.GetNormal()) - aPlane.GetSelfProjection() < aSphere.myRadius)
		{
			return true;
		}

		return false;
	}

	inline bool SphereVsFrustum(const Sphere & aSphere, const Fov90Frustum & aFrustum)
	{
		if (SphereVsPlane(aSphere, aFrustum.myDownPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myFarPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myLeftPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myNearPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myRightPlane) == true &&
			SphereVsPlane(aSphere, aFrustum.myTopPlane) == true)
		{
			return true;
		}

		return false;
	}

	inline bool AABBVsPlane(const AABB & aAABB, const Plane<float> & aPlane)
	{
		// These two lines not necessary with a (center, extents) AABB representation
		CU::Point3f c = aAABB.myCenterPos;// Compute AABB center

		CU::Point3f e = aAABB.myExtents; // Compute positive extents

										 // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
		float r = e.x * abs(aPlane.GetNormal().x) + e.y * abs(aPlane.GetNormal().y) + e.z * abs(aPlane.GetNormal().z);

		// Compute distance of box center from plane
		float s = aPlane.GetNormal().Dot(c) - aPlane.GetDistanceFromOrigin();

		// Intersection occurs when distance s falls within [-r,+r] interval
		return abs(s) <= r;
	}

	inline bool AABBVsFrustum(const AABB & aAABB, const Fov90Frustum & aFrustum)
	{
		if (AABBVsPlane(aAABB, aFrustum.myDownPlane) == true &&
			AABBVsPlane(aAABB, aFrustum.myFarPlane) == true &&
			AABBVsPlane(aAABB, aFrustum.myLeftPlane) == true &&
			AABBVsPlane(aAABB, aFrustum.myNearPlane) == true &&
			AABBVsPlane(aAABB, aFrustum.myRightPlane) == true &&
			AABBVsPlane(aAABB, aFrustum.myTopPlane) == true)
		{
			return true;
		}

		return false;
	}
	
	inline bool KnownPointVsLineSegment(CU::Vector2f aPoint, const Intersection2D::LineSegment2D & aLine)
	{
		const float LineLength = (aLine.myEndPos - aLine.myStartPos).Length2();
	
		const float pointLength1 = (aPoint - aLine.myStartPos).Length2();
		const float pointLength2 = (aPoint - aLine.myEndPos).Length2();

		if (pointLength1 > LineLength ||
			pointLength2 > LineLength)
		{
			return false;
		}

		return true;
	}

	inline bool LineVsLine(const Intersection2D::LineSegment2D & aFirstLine, const Intersection2D::LineSegment2D & aSecondLine, CU::Vector3f & anIntersectionPoint)
	{
		const CU::Vector2f Line1 = aFirstLine.myEndPos - aFirstLine.myStartPos;
		const CU::Vector2f Line2 = aSecondLine.myEndPos - aSecondLine.myStartPos;

		const CU::Vector2f Line1Normal = CU::Vector2f(-Line1.y, Line1.x).Normalize();
		
		const CU::Vector2f Line2Normal = CU::Vector2f(-Line2.y, Line2.x).Normalize();
		
		const float Line1DistanceFromZero = CU::Vector2f::Dot(Line1Normal, aFirstLine.myStartPos);
		const float Line2DistanceFromZero = CU::Vector2f::Dot(Line2Normal, aSecondLine.myStartPos);

		const float numeratorX = (Line2Normal.y * Line1DistanceFromZero) - (Line1Normal.y * Line2DistanceFromZero);
		const float numeratorY = (Line1Normal.x * Line2DistanceFromZero) - (Line2Normal.x * Line1DistanceFromZero);

		const float denominator = (Line1Normal.x * Line2Normal.y) - (Line2Normal.x * Line1Normal.y);

		if (denominator == 0)
		{
			if (numeratorX == 0 && numeratorY == 0)
			{
				const float Line1Length = Line1.Length();
				const float Line2Length = Line2.Length();

				const CU::Vector2f Line1Normalized = Line1.GetNormalized();
				const CU::Vector2f Line2Normalized = Line2.GetNormalized();
				

				
				if (Line1Normalized.Dot(aSecondLine.myEndPos - aFirstLine.myStartPos) < Line1Length &&
					Line1Normalized.Dot(aSecondLine.myEndPos - aFirstLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aSecondLine.myEndPos;
					return true;
				}



				if (Line1Normalized.Dot(aSecondLine.myStartPos - aFirstLine.myStartPos) < Line1Length &&
					Line1Normalized.Dot(aSecondLine.myStartPos - aFirstLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aSecondLine.myStartPos;
					return true;
				}


				if (Line1Normalized.Dot(aFirstLine.myEndPos - aSecondLine.myStartPos) < Line2Length &&
					Line1Normalized.Dot(aFirstLine.myEndPos - aSecondLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aFirstLine.myEndPos;
					return true;
				}


				if (Line1Normalized.Dot(aFirstLine.myStartPos - aSecondLine.myStartPos) < Line2Length &&
					Line1Normalized.Dot(aFirstLine.myStartPos - aSecondLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aFirstLine.myStartPos;
					return true;
				}
				
				return false;

			}

			return false;
		}

		CU::Vector2f tempPoint;

		tempPoint.x = numeratorX / denominator;
		tempPoint.y = numeratorY / denominator;

		if (KnownPointVsLineSegment(tempPoint, aFirstLine) == false ||
			KnownPointVsLineSegment(tempPoint, aSecondLine) == false)
		{
			return false;
		}

		anIntersectionPoint.x = tempPoint.x;
		anIntersectionPoint.y = tempPoint.y;

		return true;
	}
};