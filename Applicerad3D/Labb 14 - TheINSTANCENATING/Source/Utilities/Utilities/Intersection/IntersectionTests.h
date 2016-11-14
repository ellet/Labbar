#pragma once



namespace ENGINE_NAMESPACE
{
	class SphereCollider;
	class RayCollider;
	struct CollisionData;

	namespace Intersection
	{
		bool SphereVsSphere(const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere);
		bool SphereVsSphere(CollisionData & aCollisionData, const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere);

		bool CapsuleVsSphere(const CapsuleCollider & aCapsuleCollider, const SphereCollider & aSphereCollider);
		bool CapsuleVsCapsule(const CapsuleCollider & aCapsuleCollider, const CapsuleCollider & aAnotherCapsule);

		bool RayVsCapsule(const RayCollider & aRay, const CapsuleCollider & aCapsuleColliders);

		bool RayVsSphere(const RayCollider & aRay, const SphereCollider & aSphere);
		bool RayVsSphere(CollisionData & aCollisionData, const RayCollider & aRay, const SphereCollider & aSphere);
		bool RayVsSphere(GrowingArray<CollisionData> & aCollisionData, const RayCollider & aRay, const SphereCollider & aSphere);
	}

}