#pragma once
#include "ColliderData.h"
#include "Engine/Physics/CollisionData.h"


namespace ENGINE_NAMESPACE
{
	class SphereCollider;

	typedef SphereCollider CollisionCollider;

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		bool CheckCollisionsAgainstCollider(const ColliderData & aColliderData, CollisionData & aCollisionData);

		void AddCollisionCollider(const ColliderData & aColliderDataToAdd);
		void RemoveCollisionCollider(const ColliderData & aColliderDataToRemove);

		void AddTriggerCollider(const ColliderData & aColliderDataToAdd);
		void RemoveTriggerCollider(const ColliderData & aColliderDataRemove);

		void Update();


	private:

		bool CheckIfShouldCollide(const ColliderData & aLeft, const ColliderData & aRight);
		void CheckTriggers();
		bool CheckCollision(CollisionData & aCollisionData, const CollisionCollider & aFirstColliderToCheck, const CollisionCollider & aColliderToCheckAgainst);
		bool CheckTrigger(const CollisionCollider & aFirstColliderToCheck, const CollisionCollider & aColliderToCheckAgainst);

		GrowingArray<ColliderData> myCollisionColliders;
		GrowingArray<ColliderData> myTriggerColliders;
	};

}

