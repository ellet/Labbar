#include "stdafx.h"
#include "Engine\Resources\ResourceManager.h"
#include "Engine\FileWatcher\FileChangeWatcher.h"

namespace
SB
{
	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
		RemoveAllResources();
	}

	void ResourceManager::Update()
	{
	}

	void ResourceManager::CleanUp()
	{
		GrowingArray<LoadedResource*> resources;

		PrepareCleanUp(resources);

		for (unsigned short i = 0; i < resources.Size(); i++)
		{
			if (resources[i]->IsScheduledForRemoval() == false)
			{
				Error("A resource is about to be deleted but not supposed to.");
			}
			delete resources[i];
		}
	}

	void ResourceManager::PrepareCleanUp(GrowingArray<LoadedResource*> & aResources)
	{
		unsigned short previousCount = aResources.Size();

		mySynchronizationMutex.lock();
		GrowingArray<std::string> keysToRemove;
		for (auto&& it : myLoadedResources)
		{
			if (it.second->IsScheduledForRemoval())
			{
				aResources.Add(it.second.release());
				keysToRemove.Add(it.first);
			}
		}
		for (unsigned short i=0; i<keysToRemove.Size();  i++)
		{
			myLoadedResources.erase(myLoadedResources.find(keysToRemove[i]));
		}
		mySynchronizationMutex.unlock();

		for (unsigned short i = previousCount; i < aResources.Size(); i++)
		{
			aResources[i]->PrepareRemoval();
		}

		// Deleting resources that are still loading may finish loading dependencies, therefore do an extra pass if we deleted something
		if (aResources.Size() - previousCount > 0)
		{
			PrepareCleanUp(aResources);
		}
	}

	void ResourceManager::RemoveAllResources()
	{
		GrowingArray<LoadedResource*> resources;

		PrepareRemoveAllResources(resources);
		
		for (unsigned short i = 0; i < resources.Size(); i++)
		{
			delete resources[i];
		}
	}

	void ResourceManager::PrepareRemoveAllResources(GrowingArray<LoadedResource*> & aResources)
	{
		unsigned short previousCount = aResources.Size();

		mySynchronizationMutex.lock();
		for (auto&& it : myLoadedResources)
		{
			aResources.Add(it.second.release());
		}
		myLoadedResources.clear();
		mySynchronizationMutex.unlock();
		
		for (unsigned short i = previousCount; i < aResources.Size(); i++)
		{
			aResources[i]->PrepareRemoval();
		}

		// Deleting resources that are still loading may finish loading dependencies, therefore do an extra pass if we deleted something
		if (aResources.Size() - previousCount > 0)
		{
			PrepareRemoveAllResources(aResources);
		}
	}

	ReceiveResult ResourceManager::Receive(const FileChangedEvent& aMessage)
	{
		std::cout << aMessage.GetPath() << std::endl;

		std::lock_guard<std::mutex> lg(mySynchronizationMutex);

		auto&& it = myLoadedResources.find(aMessage.GetPath());

		if (it != myLoadedResources.end())
		{
			it->second->Get()->Reload();
		}

		return ReceiveResult::eContinue;
	}

	const std::string& Resource::GetPath() const
	{
		return myPath;
	}

	LoadedResource::LoadedResource(Resource* aResource, const std::string& aPath, bool aIsPermanentlyLoaded)
	{
		myResource = std::unique_ptr<Resource>(aResource);
		myIsScheduledForRemoval = true;
		if (aIsPermanentlyLoaded)
		{
			myIsScheduledForRemoval = false;
			myPermanentLock = std::shared_ptr<Resource>(myResource.get(), std::bind(&LoadedResource::ScheduleForRemoval, this));
			myCurrentSmartPtr = myPermanentLock;
		}
	}

	LoadedResource::~LoadedResource()
	{
	}

	std::shared_ptr<Resource> LoadedResource::Get()
	{
		std::shared_ptr<Resource> resource = myCurrentSmartPtr.lock();
		if (resource == nullptr && myIsScheduledForRemoval)
		{
			resource = std::shared_ptr<Resource>(myResource.get(), std::bind(&LoadedResource::ScheduleForRemoval, this));
			myCurrentSmartPtr = resource;
			myIsScheduledForRemoval = false;
		}
		return resource;
	}

	void LoadedResource::ScheduleForRemoval()
	{
		if (myPermanentLock == nullptr)
		{
			myIsScheduledForRemoval = true;
		}
	}

	bool LoadedResource::IsScheduledForRemoval() const
	{
		return myIsScheduledForRemoval && myPermanentLock == nullptr;
	}

	void LoadedResource::PrepareRemoval()
	{
		myResource->PrepareRemoval();
	}
}
