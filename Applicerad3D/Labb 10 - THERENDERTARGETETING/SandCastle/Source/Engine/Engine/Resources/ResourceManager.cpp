#include "stdafx.h"
#include "Engine\Resources\ResourceManager.h"
#include "Engine\FileWatcher\FileChangeWatcher.h"

namespace ENGINE_NAMESPACE
{

	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	}

	void ResourceManager::Update()
	{
	}

	void ResourceManager::CleanUp()
	{
		GrowingArray<std::string> resourcesToRemove;

		for(auto && it : myLoadedResources)
		{
			if (it.second->IsScheduledForRemoval())
			{
				resourcesToRemove.Add(it.first);
			}
		}

		for (unsigned short i=0; i<resourcesToRemove.Size(); i++)
		{
			myLoadedResources.erase(myLoadedResources.find(resourcesToRemove[i]));
		}
	}

	ReceiveResult ResourceManager::Receive(const FileChangedEvent & aMessage)
	{
		auto &&it = myLoadedResources.find(aMessage.GetPath());

		if (it != myLoadedResources.end())
		{
			it->second->Get()->Reload();
		}

		return ReceiveResult::eContinue;
	}

	Resource::Resource(const std::string & aFilePath)
	{
		myPath = aFilePath;
	}

	Resource::~Resource()
	{
		Engine::GetLogger().LogResource("Resource \"{0}\" was unloaded!", GetPath());
	}

	const std::string & Resource::GetPath() const
	{
		return myPath;
	}

	LoadedResource::LoadedResource(Resource * aResource, const std::string& aPath, bool aIsPermanentlyLoaded)
	{
		myResource = std::unique_ptr<Resource>(aResource);
		myIsScheduledForRemoval = true;
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
		myIsScheduledForRemoval = true;
	}

	bool LoadedResource::IsScheduledForRemoval() const
	{
		return myIsScheduledForRemoval;
	}
}

