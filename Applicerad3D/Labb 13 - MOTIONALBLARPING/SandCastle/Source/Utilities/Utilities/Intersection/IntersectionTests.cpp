#include "stdafx.h"
#include "IntersectionTests.h"
#include "Utilities\Intersection\Colliders\SphereCollider.h"
#include "..\Engine\Engine\Physics\CollisionData.h"

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
	}

}