#include "CollisionManager.h"
#include "EventCollider.h"
#include "TriggerColliders\BaseTriggerCollider.h"

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
	myEventsColliders.Init(20);
	myTriggerColliders.Init(20);
	myWorldColliders.Init(20);
	myInterfaceColliders.Init(20);
}


CollisionManager::~CollisionManager()
{
}

bool CollisionManager::InsideCheckCollisionAgainstWorld(const BaseCollisionShape & aObjectToCheck) const
{
	for (unsigned short iColliders = 0; iColliders < myWorldColliders.Size(); ++iColliders)
	{
		if (aObjectToCheck.CheckCollision((*myWorldColliders[iColliders])) == true)
		{
			return true;
		}
	}

	return false;
}

bool CollisionManager::InsideCheckCollisionAgainstWorldObjects(const BaseCollisionShape & aObjectToCheck) const
{
	for (unsigned short iColliders = 0; iColliders < myEventsColliders.Size(); ++iColliders)
	{
		if (aObjectToCheck.CheckCollision(*(*myEventsColliders[iColliders]).myCollider) == true)
		{
			return true;
		}
	}

	return false;
}

void CollisionManager::InsideUpdate()
{

	bool checkWorldObjects = true;

	for (unsigned short iTriggers = 0; iTriggers < myTriggerColliders.Size(); ++iTriggers)
	{
		for (unsigned short iColliders = 0; iColliders < myInterfaceColliders.Size(); ++iColliders)
		{
			if (CheckACollision((*myTriggerColliders[iTriggers]), (*myInterfaceColliders[iColliders])) == true)
			{
				checkWorldObjects = false;
				/*myTriggerColliders.RemoveAll();
				iTriggers = 0;*/
				//break;
			}
		}
	}

	if (checkWorldObjects == true)
	{
		for (unsigned short iTriggers = 0; iTriggers < myTriggerColliders.Size(); ++iTriggers)
		{
			for (unsigned short iColliders = 0; iColliders < myEventsColliders.Size(); ++iColliders)
			{
				CheckACollision((*myTriggerColliders[iTriggers]), (*myEventsColliders[iColliders]));
			}
		}
	}

	ClearBuffers();
}

void CollisionManager::ClearBuffers()
{
	myEventsColliders.RemoveAll();
	myTriggerColliders.RemoveAll();
	myInterfaceColliders.RemoveAll();
}

bool CollisionManager::CheckACollision(const BaseTriggerCollider & aTrigger, const EventCollider & aEventCollider) const
{
	const BaseCollisionShape & TriggerShape = aTrigger.GetCollisionShape();
	const BaseCollisionShape & EventShape = *aEventCollider.myCollider;

	if (TriggerShape.CheckCollision((EventShape)) == true)
	{
		aTrigger.TriggerEvent(aEventCollider);
		return true;
	}

	return false;
	//TODO::REMOVE TEMP VARIABLES FROM TRIGGERCHECK

	/*if (aTrigger.GetCollisionShape().CheckCollision((*aEventCollider.myCollider)) == true)
	{
		aTrigger.TriggerEvent((*aEventCollider.myEvent));
		return true;
	}
	return false;
	*/
}