#include "stdafx.h"
#include "PhysicsManager.h"
#include "Engine\CollisionHandling\CollisionManager.h"
#include "PhysicsComponent.h"
#include "Engine\CollisionHandling\ColliderData.h"
#include "Engine\Component\Collider\CollisionEvent.h"
#include "Engine\Component\Collider\TriggerCollisionEvent.h"


namespace ENGINE_NAMESPACE
{

	PhysicsManager::PhysicsManager()
	{
		myCollisionManager = std::make_unique<CollisionManager>();
	}


	PhysicsManager::~PhysicsManager()
	{
	}

	void PhysicsManager::Update()
	{
		
		for (unsigned short iComponent = 0; iComponent < myPhysicsComponents.Size(); iComponent++)
		{
			ColliderData tempData = myPhysicsComponents[iComponent]->GetColliderData();
			tempData.myCollider = &myPhysicsComponents[iComponent]->GetMovedCollider();

			CollisionData collisionData;

			
			if (myPhysicsComponents[iComponent]->GetColliderIsTrigger() == true ||
				myCollisionManager->CheckCollisionsAgainstCollider(tempData, collisionData) == false)
			{
				UpdateComponentMovement(*myPhysicsComponents[iComponent]);
			}
			else
			{
				/*
					DONT LOOK AT THIS CODE ! ;)
				*/
				collisionData.mySpeed = myPhysicsComponents[iComponent]->GetSpeed();
				tempData.myGameObject->TriggerEvent(CollisionEvent(collisionData));
				myPhysicsComponents[iComponent]->HandleCollisionMovement(collisionData);

				if (collisionData.myGameObject->GetComponentCount<PhysicsComponent>() > 0)
				{
					const GameObject * tempGameObject;
					unsigned short iPhysicsComponent = 0;

					bool foundGameObject = false;

					for (; iPhysicsComponent < myPhysicsComponents.Size(); iPhysicsComponent++)
					{
						tempGameObject = &myPhysicsComponents[iPhysicsComponent]->GetGameObject();
						if (tempGameObject == collisionData.myGameObject)
						{
							foundGameObject = true;
							break;
						}
					}

					if (foundGameObject == true)
					{
						collisionData.myDirection = -collisionData.myDirection;
						collisionData.myGameObject = &myPhysicsComponents[iComponent]->GetGameObject();
						myPhysicsComponents[iPhysicsComponent]->HandleCollisionMovement(collisionData);
					}
					else
					{
						Error("physics component did not find other physics component");
					}

					
				}
			}
		}
		

		myCollisionManager->Update();
	}

	void PhysicsManager::AddPhysicsComponent(PhysicsComponent & aComponentToAdd)
	{
		myPhysicsComponents.Add(&aComponentToAdd);
	}

	void PhysicsManager::RemovePhysicsComponent(PhysicsComponent & aComponentToRemove)
	{
		myPhysicsComponents.RemoveCyclic(&aComponentToRemove);
	}

	bool PhysicsManager::RayTrace(const RayCollider & aCollider, CollisionData & aCollisionDataToBuild)
	{
		return myCollisionManager->RayTrace(aCollider, aCollisionDataToBuild);
	}

	bool PhysicsManager::RayTrace(const RayCollider & aCollider, GrowingArray<CollisionData> & aCollisionDataToBuild)
	{
		return myCollisionManager->RayTrace(aCollider, aCollisionDataToBuild);
	}


	void PhysicsManager::AddCollisionCollider(const ColliderData & aColliderData)
	{
		myCollisionManager->AddCollisionCollider(aColliderData);
	}

	void PhysicsManager::RemoveCollisionCollider(const ColliderData & aColliderData)
	{
		myCollisionManager->RemoveCollisionCollider(aColliderData);
	}

	void PhysicsManager::AddTriggerCollider(const ColliderData & aColliderData)
	{
		myCollisionManager->AddTriggerCollider(aColliderData);
	}

	void PhysicsManager::RemoveTriggerCollider(const ColliderData & aColliderData)
	{
		myCollisionManager->RemoveTriggerCollider(aColliderData);
	}

	void PhysicsManager::UpdateComponentMovement(const PhysicsComponent & aComponentToUpdate)
	{
		aComponentToUpdate.MoveObjectToPosition();
	}

}