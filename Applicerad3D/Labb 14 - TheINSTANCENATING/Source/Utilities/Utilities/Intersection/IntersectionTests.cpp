#include "stdafx.h"
#include "IntersectionTests.h"
#include "Utilities\Intersection\Colliders\SphereCollider.h"
#include "..\Engine\Engine\Physics\CollisionData.h"
#include "Utilities\Intersection\IntersectionHelpFunctions.h"

namespace ENGINE_NAMESPACE
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
		bool SphereVsSphere(CollisionData & aCollisionData, const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere)
		{
			Vector3f tempLengthDifference = aFirstSphere.GetPosition() - aSecondSphere.GetPosition();
			float tempCombinedRadius = aFirstSphere.GetRadius() + aSecondSphere.GetRadius();
			float tempDistance = tempLengthDifference.Length();

			if (tempDistance < tempCombinedRadius)
			{
				aCollisionData.myDirection = tempLengthDifference.GetNormalized();

				Vector3f tempPoint = aSecondSphere.GetPosition() + tempLengthDifference.GetNormalized() * aSecondSphere.GetRadius();
				aCollisionData.myCollisionPoint = tempPoint;

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
			return false;
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

		//int IntersectRaySphere(Point p, Vector d, Sphere s, float &t, Point &q)
		bool RayVsSphere(CollisionData & aCollisionData, const RayCollider & aRay, const SphereCollider & aSphere)
		{
			Vector3f m = aRay.GetPosition() - aSphere.GetPosition();

			float b = Vector3f::Dot(m, aRay.GetDirection());

			float c = Vector3f::Dot(m, m) - aSphere.GetRadius() * aSphere.GetRadius();

			// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)

			if (c > 0.0f && b > 0.0f)
			{
				return false;
			}

			float discr = b*b - c;

			// A negative discriminant corresponds to ray missing sphere

			if (discr < 0.0f)
			{
				return false;
			}

			// Ray now found to intersect sphere, compute smallest t value of intersection

			float t = -b - sqrt(discr);

			// If t is negative, ray started inside sphere so clamp t to zero

			if (t < 0.0f)
			{
				t = 0.0f;
			}

			aCollisionData.myCollisionPoint = aRay.GetPosition() + t * aRay.GetDirection();

			return true;
		}

		bool RayVsSphere(GrowingArray<CollisionData> & aCollisionData, const RayCollider & aRay, const SphereCollider & aSphere)
		{
			Vector3f m = aRay.GetPosition() - aSphere.GetPosition();

			float b = Vector3f::Dot(m, aRay.GetDirection());

			float c = Vector3f::Dot(m, m) - aSphere.GetRadius() * aSphere.GetRadius();

			// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)

			if (c > 0.0f && b > 0.0f)
			{
				return false;
			}

			float discr = b*b - c;

			// A negative discriminant corresponds to ray missing sphere

			if (discr < 0.0f)
			{
				return false;
			}

			// Ray now found to intersect sphere, compute smallest t value of intersection

			float t = -b - sqrt(discr);

			// If t is negative, ray started inside sphere so clamp t to zero

			if (t < 0.0f)
			{
				t = 0.0f;
			}

			aCollisionData.Add(CollisionData());
			aCollisionData.GetLast().myCollisionPoint = aRay.GetPosition() + t * aRay.GetDirection();

			return true;
		}

	}

}