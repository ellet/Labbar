#include "stdafx.h"
#include "PhysicsManager.h"
#include "Engine\CollisionHandling\CollisionManager.h"
#include "PhysicsComponent.h"
#include "..\CollisionHandling\ColliderData.h"
#include "..\Component\Collider\CollisionEvent.h"


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

			if (myCollisionManager->CheckCollisionsAgainstCollider(tempData, collisionData) == false)
			{
				UpdateComponentMovement(*myPhysicsComponents[iComponent]);
			}
			else
			{
				tempData.myGameObject->TriggerEvent(CollisionEvent(collisionData));
				myPhysicsComponents[iComponent]->HandleCollisionMovement(collisionData);
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