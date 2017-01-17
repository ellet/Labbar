#pragma once
#include "Engine\Resources\Resource.h"
#include "Engine\FileWatcher\FileChangedEvent.h"

namespace SB
{

	enum class LoadError
	{
		aSuccess,
		eNotFound,
		eWrongType,
		eCorrupted
	};
	
	template<typename TResourceType>
	class ResourceLoader
	{
	public:
		static TResourceType *Load(const std::string & aPath, LoadError & aError);
	};

	class LoadedResource
	{
	public:
		LoadedResource(Resource * aResource, const std::string &  aPath, bool aIsPermanentlyLoaded);
		~LoadedResource();

		std::shared_ptr<Resource> Get();
		void ScheduleForRemoval();
		bool IsScheduledForRemoval() const;
		
		void PrepareRemoval();

	private:
		std::unique_ptr<Resource> myResource;
		bool myIsScheduledForRemoval;
		std::shared_ptr<Resource> myPermanentLock;
		std::weak_ptr<Resource> myCurrentSmartPtr;
	};

	class ResourceManager : public Subscriber<FileChangedEvent>
	{
	public:
		ResourceManager();
		~ResourceManager();
		void Update();

		template <typename TResourceType>
		std::shared_ptr<TResourceType> Get(const std::string &aPath, LoadError * aError = nullptr, bool aIsPermanentlyLoaded = false);

		void CleanUp();
		void RemoveAllResources();
		ReceiveResult Receive(const FileChangedEvent& aMessage) override;

	private:
		void PrepareCleanUp(GrowingArray<LoadedResource*>& aResources);
		void PrepareRemoveAllResources(GrowingArray<LoadedResource*>& aResources);

		std::unordered_map<std::string, std::unique_ptr<LoadedResource>> myLoadedResources;
		std::mutex mySynchronizationMutex;
	};

	template <typename TResourceType>
	TResourceType *ResourceLoader<TResourceType>::Load(const std::string& aPath, LoadError& aError)
	{
		static_assert(false, "The resource loader for this type does not exist or was not included!");
	}

	template <typename TResourceType>
	std::shared_ptr<TResourceType> ResourceManager::Get(const std::string& aPath, LoadError * aError, bool aIsPermanentlyLoaded)
	{
		mySynchronizationMutex.lock();
		auto &&it = myLoadedResources.find(aPath);

		if (it != myLoadedResources.end())
		{
			std::shared_ptr<TResourceType> resource = std::static_pointer_cast<TResourceType>(it->second->Get());
			mySynchronizationMutex.unlock();
			return resource;
		}

		mySynchronizationMutex.unlock();

		Stopwatch watch;
		LoadError error = LoadError::aSuccess;
		LoadError & errorToSet = aError != nullptr ? *aError : error;

		Engine::GetLogger().LogResource("Beginning to load resource \"{0}\".", aPath);

		TResourceType * resource = ResourceLoader<TResourceType>::Load(aPath, errorToSet);

		if (resource == nullptr)
		{
			switch (errorToSet)
			{
			case LoadError::eCorrupted:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". File is corrupted."));
			case LoadError::eNotFound:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". File not found."));
			case LoadError::eWrongType:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". Invalid Type."));
			case LoadError::aSuccess:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". Error not set."));
			default:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". Unknown error (") + std::to_string(static_cast<int>(errorToSet)) + std::string(")."));
			}
		}

		LoadedResource * resourceContainer = new LoadedResource(resource, aPath, aIsPermanentlyLoaded);

		mySynchronizationMutex.lock();

		// If someone else finished loading the resource while we loaded it
		if (myLoadedResources.find(aPath) != myLoadedResources.end())
		{
			mySynchronizationMutex.unlock();
			delete resourceContainer;
			Engine::GetLogger().LogWarning("Someone else finished loading resource {0} before we finished loading it! =(", aPath);
			return Get<TResourceType>(aPath, aError, aIsPermanentlyLoaded);
		}

		myLoadedResources.emplace(aPath, std::unique_ptr<LoadedResource>(resourceContainer));
		mySynchronizationMutex.unlock();

		Engine::GetLogger().LogResource("Resource \"{0}\" loaded in {1}ms", aPath, watch.GetElapsedTime().InMilliseconds());

		return std::static_pointer_cast<TResourceType>(resourceContainer->Get());
	}
}
