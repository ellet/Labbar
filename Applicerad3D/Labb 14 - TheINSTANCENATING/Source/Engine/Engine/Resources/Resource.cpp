#include "stdafx.h"
#include "Resource.h"

namespace ENGINE_NAMESPACE
{
	Resource::Resource(const std::string & aFilePath)
	{
		myPath = aFilePath;
		myStatus = ResourceStatus::eReady;
	}

	void Resource::SetStatus(const ResourceStatus& aStatus)
	{
		myStatus = aStatus;
	}

	Resource::~Resource()
	{
		Engine::GetLogger().LogResource("Resource \"{0}\" was unloaded!", GetPath());
	}

	void Resource::PrepareRemoval()
	{
	}
}
