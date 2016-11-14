#include "stdafx.h"
#include "CollisionManager.h"
#include "Utilities\Intersection\IntersectionTests.h"
#include "Engine\\Component\Collider\CollisionEvent.h"
#include "Engine\GameObject\GameObject.h"
#include "Engine\Component\Collider\TriggerCollisionEvent.h"



namespace ENGINE_NAMESPACE
{
	CollisionManager::CollisionManager()
	{
	}


	CollisionManager::~CollisionManager()
	{
	}

	void CollisionManager::AddCollisionCollider(const ColliderData & aColliderDataToAdd)
	{
		myCollisionColliders.Add(aColliderDataToAdd);
	}

	void CollisionManager::RemoveCollisionCollider(const ColliderData & aColliderDataToRemove)
	{
		myCollisionColliders.RemoveCyclic(aColliderDataToRemove);
	}

	void CollisionManager::AddTriggerCollider(const ColliderData & aColliderDataToAdd)
	{
		myTriggerColliders.Add(aColliderDataToAdd);
	}

	void CollisionManager::RemoveTriggerCollider(const ColliderData & aColliderDataToRemove)
	{
		myTriggerColliders.RemoveCyclic(aColliderDataToRemove);
	}

	void CollisionManager::Update()
	{
		CheckTriggers();
	}

	bool CollisionManager::CheckCollisionsAgainstCollider(const ColliderData & aColliderData, CollisionData & aCollisionData)
	{
		for (unsigned short iCollider = 0; iCollider < myCollisionColliders.Size(); ++iCollider)
		{

			if (CheckIfShouldCollide(myCollisionColliders[iCollider], aColliderData) == false)
			{
				continue;
			}

			if (CheckCollision(aCollisionData, *aColliderData.myCollider, *myCollisionColliders[iCollider].myCollider) == true)
			{
				CollisionData tempCollisionData = aCollisionData;
				tempCollisionData.myGameObject = aColliderData.myGameObject;
				tempCollisionData.myColliderIndex = myCollisionColliders[iCollider].myColliderIndex;

				aCollisionData.myGameObject = myCollisionColliders[iCollider].myGameObject;
				aCollisionData.myColliderIndex = aColliderData.myColliderIndex;

				myCollisionColliders[iCollider].myGameObject->TriggerEvent(CollisionEvent(tempCollisionData));
				return true;
			}
		}

		return false;
	}

	bool CollisionManager::RayTrace(const RayCollider & aRayCollider, CollisionData & aCollisionDataToBuild)
	{
		for (unsigned short iCollider = 0; iCollider < myCollisionColliders.Size(); ++iCollider)
		{
			if (Intersection::RayVsSphere(aCollisionDataToBuild, aRayCollider, *myCollisionColliders[iCollider].myCollider) == true)
			{
				aCollisionDataToBuild.myGameObject = myCollisionColliders[iCollider].myGameObject;
				aCollisionDataToBuild.myDirection = -aRayCollider.GetDirection();
				aCollisionDataToBuild.mySpeed = 0.f;

				return true;
			}
		}

		return false;
	}

	bool CollisionManager::RayTrace(const RayCollider & aRayCollider, GrowingArray<CollisionData> & aCollisionDataToBuild)
	{
		bool hasHit = false;

		for (unsigned short iCollider = 0; iCollider < myCollisionColliders.Size(); ++iCollider)
		{
			if (Intersection::RayVsSphere(aCollisionDataToBuild, aRayCollider, *myCollisionColliders[iCollider].myCollider) == true)
			{
				aCollisionDataToBuild.GetLast().myGameObject = myCollisionColliders[iCollider].myGameObject;
				aCollisionDataToBuild.GetLast().myDirection = -aRayCollider.GetDirection();
				aCollisionDataToBuild.GetLast().mySpeed = 0.f;

				hasHit = true;
			}
		}

		return hasHit;
	}

	bool CollisionManager::CheckIfShouldCollide(const ColliderData & aLeft, const ColliderData & aRight)
	{
		if (aLeft.myGameObject == aRight.myGameObject)
		{
			return false;
		}

		if ((*aLeft.myLayerID) & (*aRight.myCollisionFilter))
		{
			return true;
		}

		if ((*aRight.myLayerID) & (*aLeft.myCollisionFilter))
		{
			return true;
		}

		return false;
	}

	void CollisionManager::CheckTriggers()
	{
		for (unsigned short iCollider = 0; iCollider < myCollisionColliders.Size(); ++iCollider)
		{
			for (unsigned short iTrigger = 0; iTrigger < myTriggerColliders.Size(); ++iTrigger)
			{
				if (CheckIfShouldCollide(myCollisionColliders[iCollider], myTriggerColliders[iTrigger]) == false)
				{
					continue;
				}

				if (CheckTrigger(*myCollisionColliders[iCollider].myCollider, *myTriggerColliders[iTrigger].myCollider) == true)
				{
					CheckIfShouldCollide(myCollisionColliders[iCollider], myTriggerColliders[iTrigger]);
					myTriggerColliders[iTrigger].myGameObject->TriggerEvent(TriggerCollisionEvent(*myCollisionColliders[iCollider].myGameObject, *myCollisionColliders[iCollider].myCollider, myTriggerColliders[iTrigger].myColliderIndex));
					myCollisionColliders[iCollider].myGameObject->TriggerEvent(TriggerCollisionEvent(*myTriggerColliders[iTrigger].myGameObject, *myTriggerColliders[iTrigger].myCollider, myCollisionColliders[iCollider].myColliderIndex));
				}
			}
		}
	}

	bool CollisionManager::CheckCollision(CollisionData & aCollisionData, const CollisionCollider & aFirstColliderToCheck, const CollisionCollider & aColliderToCheckAgainst)
	{
		if(Intersection::SphereVsSphere(aCollisionData, aFirstColliderToCheck, aColliderToCheckAgainst) == true)
		{
			return true;
		}
		return false;
	}

	bool CollisionManager::CheckTrigger(const CollisionCollider & aFirstColliderToCheck, const CollisionCollider & aColliderToCheckAgainst)
	{
		if (Intersection::SphereVsSphere(aFirstColliderToCheck, aColliderToCheckAgainst) == true)
		{
			return true;
		}

		return false;
	}

}
