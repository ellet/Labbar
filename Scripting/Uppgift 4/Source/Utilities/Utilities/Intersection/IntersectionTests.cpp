#include "stdafx.h"
#include "IntersectionTests.h"
#include "Utilities\Intersection\Colliders\SphereCollider.h"
#include "Utilities\Intersection\IntersectionHelpFunctions.h"

namespace SB
{

	namespace Intersection
	{
		bool SphereVsSphere(const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere)
		{
			Vector3f tempLengthDifference = aFirstSphere.GetPosition() - aSecondSphere.GetPosition();
			float tempCombinedRadius = aFirstSphere.GetRadius() + aSecondSphere.GetRadius();
			float tempDistance = tempLengthDifference.Length();

			if (tempDistance < tempCombinedRadius)
			{
				return true;
			}

			return false;
		}
		

		bool CapsuleVsSphere(const CapsuleCollider & aCapsuleCollider, const SphereCollider & aSphereCollider)
		{
			const float dist2 = Intersection::DistanceFromPointToLineSegment(aCapsuleCollider.GetCapsuleAsLineSegment(), aSphereCollider.GetPosition());

			const float CombinedRadius = aCapsuleCollider.GetRadius() + aSphereCollider.GetRadius();

			if (dist2 <= CombinedRadius * CombinedRadius)
			{
				return true;
			}

			return false;
		}


		

		bool CapsuleVsCapsule(const CapsuleCollider & aCapsuleCollider, const CapsuleCollider & aAnotherCapsule)
		{
			float tempDistanceAlongFirstLine;
			float tempDistanceAlongSecondLine;

			Vector3f tempFirstClosestPoint;
			Vector3f tempSecondClosestPoint;

			float tempDistanceBetweenTheLines = Intersection::DistanceFromLineSegmtToLineSegment(aCapsuleCollider.GetCapsuleAsLineSegment(), aAnotherCapsule.GetCapsuleAsLineSegment()
				, tempDistanceAlongFirstLine, tempDistanceAlongSecondLine, tempFirstClosestPoint, tempSecondClosestPoint);

			float tempCombinedRadius = aCapsuleCollider.GetRadius() + aAnotherCapsule.GetRadius();

			if (tempDistanceBetweenTheLines <= tempCombinedRadius * tempCombinedRadius)
			{
				return true;
			}

			return false;
		}


		bool RayVsCapsule(const RayCollider & aRay, const CapsuleCollider & aCapsuleColliders)
		{
			Vector3f derp;
			float dist2 = DistanceFromLineSegmentToRay(aCapsuleColliders.GetCapsuleAsLineSegment(), aRay, derp);

			if (dist2 <= aCapsuleColliders.GetRadius() * aCapsuleColliders.GetRadius())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

				
		bool RayVsSphere(const RayCollider & aRay, const SphereCollider & aSphere)
		{
			Vector3f m = aRay.GetPosition() - aSphere.GetPosition();

			float c = Vector3f::Dot(m, m) - aSphere.GetRadius() * aSphere.GetRadius();

			// If there is definitely at least one real root, there must be an intersection

			if (c <= 0.0f)
			{
				return true;
			}

			float b = Vector3f::Dot(m, aRay.GetDirection());

			// Early exit if ray origin outside sphere and ray pointing away from sphere

			if (b > 0.0f)
			{
				return false;
			}

			float disc = b*b - c;

			// A negative discriminant corresponds to ray missing sphere

			if (disc < 0.0f)
			{
				return false;
			}

			// Now ray must hit sphere

			return true;
		}

	}

}