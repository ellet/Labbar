#include "stdafx.h"
#include "AsynchronousResource.h"
#include <Utilities/ThreadNamer.h>

namespace SB
{
	AsynchronousResource::AsynchronousResource(const std::string & aFilePath)
		: Resource(aFilePath)
	{
		SetStatus(ResourceStatus::eNotStartedLoading);
		myLoadThread = nullptr;
		myFinishedLoadingFlag.store(false);
	}

	AsynchronousResource::~AsynchronousResource()
	{
		PrepareRemoval();
	}

	bool AsynchronousResource::Prepare(bool aLoadAsynchronously)
	{
		if (GetStatus() == ResourceStatus::eReady)
		{
			return true;
		}

		if (GetStatus() == ResourceStatus::ePreparing)
		{
			if (myFinishedLoadingFlag.load() == true)
			{
				SetStatus(ResourceStatus::eReady);
				return true;
			}
			if (aLoadAsynchronously == false)
			{
				while (myFinishedLoadingFlag.load() == false)
				{
					Sleep(1);
				}

				SetStatus(ResourceStatus::eReady);
				return true;
			}
			return false;
		}

		if (aLoadAsynchronously)
		{
			SetStatus(ResourceStatus::ePreparing);
			myLoadThread = new std::thread(std::function<void()>([this] { SetThreadName(FormatString("{0}", GetPath().c_str()).c_str()); Load(); myFinishedLoadingFlag.store(true); }));
			return false;
		}
		else
		{
			Load();
			SetStatus(ResourceStatus::eReady);
			myFinishedLoadingFlag.store(true);
			return true;
		}
	}

	void AsynchronousResource::PrepareRemoval()
	{
		if (myLoadThread != nullptr)
		{
			myLoadThread->join();

			delete myLoadThread;
			myLoadThread = nullptr;
		}
		
		SetStatus(ResourceStatus::eRemoved);
	}
}
