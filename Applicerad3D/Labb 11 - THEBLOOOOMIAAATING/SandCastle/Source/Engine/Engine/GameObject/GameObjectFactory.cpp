#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

namespace ENGINE_NAMESPACE
{
	int GameObjectFactory::Count() const
	{
		int counter = 0;
		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myObjectsActiveTag[iComponent] == true)
			{
				counter++;
			}
		}
		return counter;
	}
	
	GameObjectFactory::~GameObjectFactory()
	{
		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myObjectsActiveTag[iComponent] == true)
			{
				Error("An object was never returned! Memory was leaked!");
			}
		}
		free(myObjects);
		myObjects = nullptr;
	}

	GameObjectFactory::GameObjectFactory()
	{
		myNumberOfComponents = 8192;
		myObjects = static_cast<GameObject*>(malloc(sizeof(GameObject) * myNumberOfComponents));
		myObjectsActiveTag.Resize(myNumberOfComponents);
		for (unsigned short i = 0; i < myNumberOfComponents; i++)
		{
			myFreeMemorySlots.Push(i);
			myObjectsActiveTag[i] = false;
		}
	}

	void GameObjectFactory::ReturnMemory(unsigned short aIndex)
	{
		// Engine::GetLogger().LogInfo("Index {0} returned to factory.", aIndex);

		myObjects[aIndex].~GameObject();
		myFreeMemorySlots.Push(aIndex);
		myObjectsActiveTag[aIndex] = false;
	}

	ObjectPtr GameObjectFactory::CreateObject(Scene & aScene, const std::string & aIdentifier)
	{
		unsigned short index = GetAndActivateIndex();
		std::atomic<int> * referenceCounter = new std::atomic<int>(1);
		new (&myObjects[index]) GameObject(aScene, aIdentifier, *referenceCounter, index);

		return ObjectPtr(&myObjects[index], referenceCounter);
	}

	unsigned short GameObjectFactory::GetAndActivateIndex()
	{
		if (myFreeMemorySlots.Size() == 0)
		{
			Error("Object Factory is empty, tell a programmer it needs more slots!");
		}

		unsigned short index = myFreeMemorySlots.Pop();
		myObjectsActiveTag[index] = true;
		return index;
	}
}
