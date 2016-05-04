#include "CollisionManager.h"
#include "EventCollider.h"

#include "CollisionData/CollisionData.h"
#include "../BaseClasses/BaseGameObject/BaseGameObject.h"


CollisionManager * CollisionManager::ourInstance;

void CollisionManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new CollisionManager();
	}
}


void CollisionManager::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;

		ourInstance = nullptr;
	}
}



CollisionManager::CollisionManager()
{
	myCollisionData.Init(100);
	myWorldColliders.Init(5);
}


CollisionManager::~CollisionManager()
{
}


void CollisionManager::InsideUpdate()
{
	for (size_t iCollison = 0; iCollison < myCollisionData.Size(); ++iCollison)
	{
		for (size_t iWCollison = 0; iWCollison < myWorldColliders.Size(); ++iWCollison)
		{
			CheckACollision((*myWorldColliders[iWCollison]), (*myCollisionData[iCollison]));
		}
	}

	ClearBuffers();
}

void CollisionManager::ClearBuffers()
{
	myCollisionData.RemoveAll();
	myWorldColliders.RemoveAll();
}

void CollisionManager::CheckACollision(const CollisionData & aFirstCollider, const CollisionData & aSecondCollider) const
{
	if (aFirstCollider.myCollisionShape->CheckCollision(*aSecondCollider.myCollisionShape))
	{
		if (aFirstCollider.myObject != nullptr)
		{
			aFirstCollider.myObject->OnCollision(aSecondCollider);
		}

		if (aSecondCollider.myObject != nullptr)
		{
			aSecondCollider.myObject->OnCollision(aFirstCollider);
		}
	}
}