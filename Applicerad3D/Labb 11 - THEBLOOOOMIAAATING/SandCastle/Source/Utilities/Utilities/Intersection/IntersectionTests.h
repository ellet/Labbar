#pragma once

class SphereCollider;
class CollisionData;

namespace ENGINE_NAMESPACE
{

	namespace Intersection
	{
		bool SphereVsSphere(const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere);
		bool SphereVsSphere(CollisionData & aCollisionData, const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere);
	}

}